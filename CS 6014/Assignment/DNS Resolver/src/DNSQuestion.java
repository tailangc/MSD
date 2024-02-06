import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Objects;

public class DNSQuestion {
    private final String qName;
    private final int qType, qClass, offset;

    public DNSQuestion(String qName, int qType, int qClass, int offset) {
        this.qName = qName;
        this.qType = qType;
        this.qClass = qClass;
        this.offset = offset;
    }

    public static DNSQuestion decodeQuestion(DataInputStream inputStream, Position position) throws IOException {
        //Get offset position before reading labels
        int offsetPosition = position.getCurrentPosition();
        //Read question section format
        //Read QNAME field
        StringBuilder stringBuilder = new StringBuilder();
        //Read the length octet of the first label
        int lengthOctet = inputStream.readUnsignedByte();
        position.addCurrentPosition(1);
        while (lengthOctet != 0) {
            for (int i = 0; i < lengthOctet; i++) {
                //Read the byte and converts it to a character
                stringBuilder.append((char) inputStream.read());
                position.addCurrentPosition(1);
            }
            stringBuilder.append('.');
            lengthOctet = inputStream.read();
            position.addCurrentPosition(1);
        }
        //Remove extra character '.'
        stringBuilder.setLength(stringBuilder.length() - 1);
        //Read QTYPE and QCLASS fields
        int qType = inputStream.readUnsignedShort();
        int qClass = inputStream.readUnsignedShort();
        position.addCurrentPosition(4);
        return new DNSQuestion(stringBuilder.toString(), qType, qClass, offsetPosition);
    }

    public void encodeQuestion(DataOutputStream outputStream) throws IOException {
        //Write question section format
        outputStream.write(getBytes(qName));
        //Termination for qName
        outputStream.writeByte(0);
        outputStream.writeShort(qType);
        outputStream.writeShort(qClass);
    }

    public String getQName() {
        return qName;
    }

    public int getQType() {
        return qType;
    }

    public int getQClass() {
        return qClass;
    }

    public int getOffset() {
        return offset;
    }

    @Override
    public String toString() {
        return "DNSQuestion{" +
                "qName='" + qName + '\'' +
                ", qType=" + qType +
                ", qClass=" + qClass +
                ", offset=" + offset +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        // Uses by hashCode()
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DNSQuestion that = (DNSQuestion) o;
        return qType == that.qType && qClass == that.qClass && offset == that.offset && Objects.equals(qName, that.qName);
    }

    @Override
    public int hashCode() {
        //Use for finding DNSRecord in DNSCache
        return Objects.hash(qName, qType, qClass, offset);
    }

    private byte[] getBytes(String value) {
        byte[] bytes = new byte[value.length() + 1];
        int count = 0;
        String[] strings = value.split("\\.");
        for (String string : strings) {
            //Get length octet byte
            bytes[count++] = (byte) string.length();
            //Get each character byte
            for (char c : string.toCharArray()) {
                bytes[count++] = (byte) c;
            }
        }
        return bytes;
    }
}