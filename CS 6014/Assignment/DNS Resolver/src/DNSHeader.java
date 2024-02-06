import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class DNSHeader {
    private final int id, flags, qdCount, anCount, nsCount, arCount;

    public DNSHeader(int id, int flags, int qdCount, int anCount, int nsCount, int arCount) {
        this.id = id;
        this.flags = flags;
        this.qdCount = qdCount;
        this.anCount = anCount;
        this.nsCount = nsCount;
        this.arCount = arCount;
    }

    public static DNSHeader decodeHeader(DataInputStream inputStream, Position position) throws IOException {
        //Read header section format
        int id = inputStream.readUnsignedShort();
        int flags = inputStream.readUnsignedShort();
        int qdCount = inputStream.readUnsignedShort();
        int anCount = inputStream.readUnsignedShort();
        int nsCount = inputStream.readUnsignedShort();
        int arCount = inputStream.readUnsignedShort();
        position.addCurrentPosition(12);
        return new DNSHeader(id, flags, qdCount, anCount, nsCount, arCount);
    }

    public static DNSHeader buildResponseHeader(DNSHeader queryHeader, DNSRecord dnsRecord) {
        //Set the flag fields with bit by bit
        int value = 0;
        value = setNthBit(value, 15);   //QR bit
        value = setNthBit(value, 8);    //RD bit
        value = setNthBit(value, 7);    //RA bit
        if (dnsRecord.getRdData().equals("0.0.0.0")) {
            //Set RCODE to 3 for nonexistent host response
            value = setNthBit(value, 0);
            value = setNthBit(value, 1);
        }
        return new DNSHeader(queryHeader.getId(), value, queryHeader.getQdCount(), 1, 0, queryHeader.getArCount());
    }

    public void writeHeader(DataOutputStream outputStream) throws IOException {
        //Write header section format
        outputStream.writeShort(id);
        outputStream.writeShort(flags);
        outputStream.writeShort(qdCount);
        outputStream.writeShort(anCount);
        outputStream.writeShort(nsCount);
        outputStream.writeShort(arCount);
    }

    public int getId() {
        return id;
    }

    public int getQr() {
        return (flags & 0x8000) >> 15;
    }

    public int getOpCode() {
        return (flags & 0x7800) >> 11;
    }

    public int getAa() {
        return (flags & 0x400) >> 10;
    }

    public int getTc() {
        return (flags & 0x200) >> 9;
    }

    public int getRd() {
        return (flags & 0x100) >> 8;
    }

    public int getRa() {
        return (flags & 0x80) >> 7;
    }

    public int getZ() {
        return (flags & 0x70) >> 4;
    }

    public int getRCode() {
        return (flags & 0xF);
    }

    public int getQdCount() {
        return qdCount;
    }

    public int getAnCount() {
        return anCount;
    }

    public int getArCount() {
        return arCount;
    }

    public String toString() {
        return "DNSHeader{" +
                "ID=" + id +
                ", QR=" + getQr() +
                ", Opcode=" + getOpCode() +
                ", AA=" + getAa() +
                ", TC=" + getTc() +
                ", RD=" + getRd() +
                ", RA=" + getRa() +
                ", Z=" + getZ() +
                ", RCODE=" + getRCode() +
                ", QDCOUNT=" + qdCount +
                ", ANCOUNT=" + anCount +
                ", NSCOUNT=" + nsCount +
                ", ARCOUNT=" + arCount +
                '}';
    }

    private static int setNthBit(int value, int nth) {
        //Set the bit at the nth position in int value (4 bytes)
        return ((1 << nth) | value);
    }
}