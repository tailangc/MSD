import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.Arrays;

public class DNSRecord {
    private final String name, rData;
    private final byte[] nameOffset;
    private final int rType, rClass, rLength;
    private final long ttl;
    private final LocalDateTime expiredDateTime;

    public DNSRecord(String name, byte[] nameOffset, int rType, int rClass, long ttl, int rLength, String rData) {
        this.name = name;
        this.nameOffset = nameOffset;
        this.rType = rType;
        this.rClass = rClass;
        this.ttl = ttl;
        this.rLength = rLength;
        this.rData = rData;
        this.expiredDateTime = LocalDateTime.now().plusSeconds(ttl);
    }

    public static DNSRecord decodeRecord(DataInputStream inputStream, DNSQuestion dnsQuestion, Position position) throws IOException {
        //Read resource record format
        //Read NAME field
        int lengthOctet = inputStream.readUnsignedByte();
        position.addCurrentPosition(1);

        //Check message compression scheme
        String name = null;
        byte[] nameOffset = null;
        //check if the question has been asked before
        if ((lengthOctet & 0xC0) == 0xC0) {
            nameOffset = new byte[2];
            //Read message compression scheme and store in byte set
            nameOffset[0] = (byte) lengthOctet;
            nameOffset[1] = (byte) inputStream.readUnsignedByte();
            position.addCurrentPosition(1);
            //Get name from DNSQuestion if offset matches
            if ((nameOffset[0] << 8 | nameOffset[0]) == dnsQuestion.getOffset())
                name = dnsQuestion.getQName();
        } else {
            StringBuilder stringBuilder = new StringBuilder();
            while (lengthOctet != 0) {
                for (int i = 0; i < lengthOctet; i++) {
                    stringBuilder.append((char) inputStream.read()); //Read the byte and convert to character
                    position.addCurrentPosition(1);
                }
                stringBuilder.append('.');
                lengthOctet = inputStream.read();
                position.addCurrentPosition(1);
            }
            //Remove extra '.' at the end
            stringBuilder.setLength(stringBuilder.length() - 1);
            name = stringBuilder.toString();
        }

        //Read TYPE, CLASS, TTL, and RDLENGTH fields
        int rType = inputStream.readUnsignedShort();
        int rClass = inputStream.readUnsignedShort();
        long ttl = inputStream.readInt();
        int rdLength = inputStream.readUnsignedShort();
        position.addCurrentPosition(10);

        byte[] rdData = inputStream.readNBytes(rdLength);
        position.addCurrentPosition(rdLength);
        StringBuilder rdDataBuilder = new StringBuilder();
        for (byte rd : rdData) {
            //Convert byte to unsigned value
            rdDataBuilder.append(rd & 0xFF);
            rdDataBuilder.append('.');
        }
        //Remove extra character '.'
        rdDataBuilder.setLength(rdDataBuilder.length() - 1);
        return new DNSRecord(name, nameOffset, rType, rClass, ttl, rdLength, rdDataBuilder.toString());
    }

    public void writeRecord(DataOutputStream outputStream) throws IOException {
        //Write resource record format
        if (nameOffset != null) {
            outputStream.write(nameOffset);
        }
        else {
            outputStream.write(getCharacterBytes(name));
        }
        outputStream.writeShort(rType);
        outputStream.writeShort(rClass);
        outputStream.writeInt((int) ttl);
        outputStream.writeShort(rLength);
        outputStream.write(getBytes(rData));
    }

    public String getRdData() {
        return rData;
    }

    private byte[] getBytes(String value) {
        String[] strings = value.split("\\.");
        byte[] bytes = new byte[strings.length];
        int count = 0;
        for (String string : strings) {
            bytes[count++] = (byte) Short.parseShort(string);
        }
        return bytes;
    }

    private byte[] getCharacterBytes(String value) {
        byte[] bytes = new byte[value.length() + 1];
        int counter = 0;
        String[] strings = value.split("\\.");
        for (String string : strings) {
            //Get length octet byte
            bytes[counter++] = (byte) string.length();
            //Get each character byte
            for (char c : string.toCharArray()) {
                bytes[counter++] = (byte) c;
            }
        }
        return bytes;
    }

    @Override
    public String toString() {
        return "DNSRecord{" +
                "name='" + name + '\'' +
                ", nameOffset=" + Arrays.toString(nameOffset) +
                ", rType=" + rType +
                ", rClass=" + rClass +
                ", rData='" + rData + '\'' +
                ", ttl=" + ttl +
                ", rdLength=" + rLength +
                '}';
    }

    public boolean isExpired() {
        return LocalDateTime.now().isBefore(expiredDateTime);
    }


}