import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class DNSMessage {
    private DNSHeader dnsHeader;
    private final ArrayList<DNSQuestion> dnsQuestions;
    private final ArrayList<DNSRecord> dnsRecords;
    private final byte[] additionalRecords;

    public DNSMessage(DNSHeader dnsHeader, ArrayList<DNSQuestion> dnsQuestions, ArrayList<DNSRecord> dnsRecords,
                      byte[] additionalRecords) {
        this.dnsHeader = dnsHeader;
        this.dnsQuestions = dnsQuestions;
        this.dnsRecords = dnsRecords;
        this.additionalRecords = additionalRecords;
    }

    public static DNSMessage decodeMessage(byte[] data) throws IOException {
        //Current input stream position
        Position position = new Position();
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(data);
        DataInputStream inputStream = new DataInputStream(byteArrayInputStream);
        //Decode data into DNSHeader
        DNSHeader dnsHeader = DNSHeader.decodeHeader(inputStream, position);
        //Decode data into DNSQuestion if Opcode is standard query
        ArrayList<DNSQuestion> dnsQuestions = new ArrayList<>();
        ArrayList<DNSRecord> dnsRecords = new ArrayList<>();
        if (dnsHeader.getOpCode() == 0) {
            //Decode questions if there is any
            for (int i = 0; i < dnsHeader.getQdCount(); i++) {
                DNSQuestion dnsQuestion = DNSQuestion.decodeQuestion(inputStream, position);
                dnsQuestions.add(dnsQuestion);
                //Decode answers if there is any
                if (dnsHeader.getQr() == 1) {
                    for (int j = 0; j < dnsHeader.getAnCount(); j++) {
                        dnsRecords.add(DNSRecord.decodeRecord(inputStream, dnsQuestion, position));
                    }
                }
            }
        }
        //Read additional records
        byte[] additionalRecords = null;
        if (dnsHeader.getArCount() == 1) {
            additionalRecords = byteArrayInputStream.readNBytes(23);
            position.addCurrentPosition(23);
        }
        byteArrayInputStream.close();
        inputStream.close();
        return new DNSMessage(dnsHeader, dnsQuestions, dnsRecords, additionalRecords);
    }

    public byte[] writeMessage() throws IOException {
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        DataOutputStream outputStream = new DataOutputStream(byteArrayOutputStream);
        //Encode DNSHeader, DNSQuestions, DNSRecords, and AdditionalRecords if exists
        dnsHeader = DNSHeader.buildResponseHeader(dnsHeader, dnsRecords.get(0));
        dnsHeader.writeHeader(outputStream);
        for (DNSQuestion dnsQuestion : dnsQuestions) {
            dnsQuestion.encodeQuestion(outputStream);
        }
        for (DNSRecord dnsRecord : dnsRecords) {
            dnsRecord.writeRecord(outputStream);
        }
        if (additionalRecords != null)
            outputStream.write(additionalRecords);
        byteArrayOutputStream.close();
        outputStream.close();
        return byteArrayOutputStream.toByteArray();
    }

    public DNSHeader getDnsHeader() {
        return dnsHeader;
    }

    public ArrayList<DNSQuestion> getDnsQuestions() {
        return dnsQuestions;
    }

    public ArrayList<DNSRecord> getDnsRecords() {
        return dnsRecords;
    }

    public void setDnsRecord(DNSRecord dnsRecord) {
        dnsRecords.add(dnsRecord);
    }

    @Override
    public String toString() {
        return "DNSMessage{" +
                "dnsHeader=" + dnsHeader +
                ", dnsQuestions=" + dnsQuestions +
                ", dnsRecords=" + dnsRecords +
                ", additionalRecords=" + Arrays.toString(additionalRecords) +
                '}';
    }
}