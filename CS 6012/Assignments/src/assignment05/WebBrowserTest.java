package assignment05;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.net.MalformedURLException;
import java.net.URL;

import static org.junit.jupiter.api.Assertions.*;

class WebBrowserTest {

    @Test
    public void test() throws MalformedURLException {
        WebBrowser w = new WebBrowser();
        w.visit(new URL("https://a"));
        w.visit(new URL("https://b"));
        w.visit(new URL("https://c"));
        Assertions.assertEquals(3, w.history().size());
    }

}