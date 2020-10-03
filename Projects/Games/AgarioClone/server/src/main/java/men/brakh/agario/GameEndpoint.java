package men.brakh.agario;

import men.brakh.agario.model.communicator.Communicator;
import men.brakh.agario.model.communicator.impl.SessionCommunicator;
import men.brakh.agario.model.game.GameField;
import men.brakh.agario.model.message.Message;
import men.brakh.agario.model.message.MessageDecoder;
import men.brakh.agario.model.message.MessageEncoder;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.websocket.*;
import javax.websocket.server.PathParam;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;

@ServerEndpoint(
        value="/{username}",
        decoders = MessageDecoder.class,
        encoders = MessageEncoder.class)
public class GameEndpoint {
    private Communicator communicator;
    private static GameField gameField = new GameField(true);
    private static Logger logger = LoggerFactory.getLogger(GameEndpoint.class);

    @OnOpen
    public void onOpen(Session session, @PathParam("username") String username) {
        logger.info("New connection: " +username);
        communicator = new SessionCommunicator(session);
        gameField.add(username, communicator);
    }

    @OnMessage
    public void onMessage(Session session, Message message) {


        switch (message.getEventType()) {
            case COORDS_CHANGING:
                gameField.move(communicator, message.getValue().getCenter());
                break;

            default:
                System.out.println("BUG" + message + message.getValue().getUsername());
        }
    }

    @OnClose
    public void onClose(Session session) throws IOException {
        gameField.kill(communicator);
    }

    @OnError
    public void onError(Session session, Throwable throwable) {
        logger.error("Endpoint Exception", throwable);
    }

}