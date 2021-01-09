package factorial;

import stack.LinkedStack;
import stack.Stack;

public class Factorial {
    private enum EntryPoint {
        CALL, RESUME
    }
    private static class Context {
        int n;
        int f;
        EntryPoint entryPoint;
        Context(int n, int f, EntryPoint entryPoint) {
            this.n = n;
            this.f = f;
            this.entryPoint = entryPoint;
        }
    }
    public static int factorial_t(int n){
        Stack<Context> stack = new LinkedStack<>();
        int return_=0;
        stack.push(new Context(n, 0, EntryPoint.CALL));
        while (!stack.isEmpty()) {
            Context context = stack.top();
            switch (context.entryPoint) {
                case CALL:
                    if (context.n == 0) {
                        return_ = 1;
                        stack.pop();
                    } else {
                        // recursive
                        context.entryPoint = EntryPoint.RESUME;
                        stack.push(new Context(context.n - 1, 0, EntryPoint.CALL));
                    }
                    break;
                case RESUME:
                    context.f = return_;
                    return_ = context.f * context.n;
                    break;
            }

        }
        return return_;

    }
    public static int factorialOriginal(int n) {
        if (n == 0)
            return 1;
        else
            return n * factorialOriginal(n - 1);
    }
    public static int factorialRec(int n) {
        int f = 0;
        if (n == 0)
            return 1;
        else{
            f = factorialRec(n - 1);
            return n * f;
        }
    }
}
