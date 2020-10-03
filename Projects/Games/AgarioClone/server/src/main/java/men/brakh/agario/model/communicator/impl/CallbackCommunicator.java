package men.brakh.agario.model.communicator.impl;

import men.brakh.agario.model.communicator.Communicator;
import men.brakh.agario.model.message.Message;

import java.util.concurrent.Callable;
import java.util.function.BiPredicate;

public class CallbackCommunicator implements Communicator {
    private Callable<Void> func;
    private BiPredicate<Message, Communicator> condition;

    public CallbackCommunicator(Callable<Void> func, BiPredicate<Message, Communicator> condition) {
        this.func = func;
        this.condition = condition;
    }


    @Override
    public void send(Message message) {
        if(condition.test(message, this)) {
            try {
                func.call();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
