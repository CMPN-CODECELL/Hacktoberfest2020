package men.brakh.agario.model.communicator;

import men.brakh.agario.model.message.Message;

public interface Communicator {
    void send(Message message);
}
