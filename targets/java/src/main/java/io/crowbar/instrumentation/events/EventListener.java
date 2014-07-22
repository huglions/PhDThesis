package io.crowbar.instrumentation.events;

public interface EventListener {
    public void startTransaction (int probe_id);

    public void endTransaction (int probe_id,
                                boolean[] hit_vector);

    public void oracle (int probe_id,
                        double error,
                        double confidence);
}