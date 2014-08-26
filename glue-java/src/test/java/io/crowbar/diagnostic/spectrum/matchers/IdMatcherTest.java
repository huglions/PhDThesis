package io.crowbar.diagnostic.spectrum.matchers;

import static org.junit.Assert.*;
import io.crowbar.diagnostic.spectrum.Spectrum;
import io.crowbar.diagnostic.spectrum.activity.Hit;
import io.crowbar.diagnostic.spectrum.unserializers.HitSpectrumUnserializer;

import java.util.BitSet;
import java.util.Scanner;

import org.junit.Test;

public class IdMatcherTest {
    @Test
    public void testTransactions () {
        ActiveProbeMatcher a = new ActiveProbeMatcher();

        String in = "10 9 0 1 0 0 0 0 0 0 0 0 0.0 0 0 0 1 0 0 0 0 0 0 0.0 1 0 0 0 0 1 0 0 0 0 0.0 0 0 0 0 0 0 0 1 0 0 0.0 0 0 0 0 0 0 0 0 1 0 0.0 0 0 1 0 0 0 0 0 0 0 1.0 0 0 0 0 1 0 0 0 0 0 1.0 0 0 0 0 0 0 1 0 0 0 1.0 0 0 0 0 0 0 0 0 0 1 1.0";


        Spectrum<Hit, ? > s = HitSpectrumUnserializer.unserialize(new Scanner(in));

        BitSet cs = a.matchProbes(s);
        BitSet ts = a.matchTransactions(s);

        IdMatcher id = new IdMatcher(ts, cs);

        assertEquals(id.matchTransactions(s).length(), 9);
    }

    @Test
    public void testProbes () {
        ActiveProbeMatcher a = new ActiveProbeMatcher();

        String in = "10 9 0 1 0 0 0 0 0 0 0 0 0.0 0 0 0 1 0 0 0 0 0 0 0.0 1 0 0 0 0 1 0 0 0 0 0.0 0 0 0 0 0 0 0 1 0 0 0.0 0 0 0 0 0 0 0 0 1 0 0.0 0 0 1 0 0 0 0 0 0 0 1.0 0 0 0 0 1 0 0 0 0 0 1.0 0 0 0 0 0 0 1 0 0 0 1.0 0 0 0 0 0 0 0 0 0 1 1.0";


        Spectrum<Hit, ? > s = HitSpectrumUnserializer.unserialize(new Scanner(in));

        BitSet cs = a.matchProbes(s);
        BitSet ts = a.matchTransactions(s);

        IdMatcher id = new IdMatcher(ts, cs);

        assertEquals(id.matchProbes(s).length(), 10);
    }
}