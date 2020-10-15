package men.brakh.agario.model.communicator.impl;

import men.brakh.agario.model.communicator.Communicator;
import men.brakh.agario.model.message.Message;

import javax.websocket.EncodeException;
import javax.websocket.Session;
import java.io.IOException;

public class SessionCommunicator implements Communicator {
    private Session session;
    public SessionCommunicator(Session session) {
        this.session = session;
    }

    @Override
    public void send(Message message) {
        try {
            session.getBasicRemote().sendObject(message);
        } catch (IOException | EncodeException ignored) {

        }
    }
}
