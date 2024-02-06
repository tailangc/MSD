import java.util.HashMap;

public class DNSCache {
    private static final HashMap<DNSQuestion, DNSRecord> DNSHashmap = new HashMap<>();

    public static void put(DNSQuestion dnsQuestion, DNSRecord dnsRecord) {
        DNSHashmap.put(dnsQuestion, dnsRecord);
    }

    public static DNSRecord get(DNSQuestion dnsQuestion) {
        DNSRecord dnsRecord = DNSHashmap.get(dnsQuestion);
        if (dnsRecord != null && !dnsRecord.isExpired()) {
            DNSHashmap.remove(dnsQuestion);
            dnsRecord = null;
        }
        return dnsRecord;
    }
}