package fibonacci;
import stack.LinkedStack;
import stack.Stack;
public class Fibonacci {
    private static class Context {
        int n;
        int f1;
        int f2;
        EntryPoint entryPoint;
        public Context(int n, int f1, int f2, EntryPoint entryPoint) {
            this.n = n;
            this.f1 = f1;
            this.f2 = f2;
            this.entryPoint = entryPoint;
        }
    }
    private enum EntryPoint {
        CALL, RESUME1, RESUME2
    }
    public static int fibonacciOrig(int n) {
        if (n <= 1)
            return n;
        else
            return fibonacciOrig(n - 1) + fibonacciOrig(n - 2);
    }
    public static int fibonacciIter(int n) {
        int return_ = 0;
        Stack<Context> stack = new LinkedStack<>();
        stack.push(new Context(n, 0, 0, EntryPoint.CALL));
        while ( !stack.isEmpty()) {
            Context context = stack.top();
            switch (context.entryPoint) {
                case CALL:
                    if (context.n <= 1) {
                        return_ = context.n;
                        stack.pop();
                    } else {
                        context.entryPoint = EntryPoint.RESUME1;
                        stack.push(new Context(context.n - 1, 0, 0,
                                EntryPoint.CALL));
                    }
                    break;
                case RESUME1:
                    context.f1 = return_;
                    context.entryPoint = EntryPoint.RESUME2;
                    stack.push(new Context(context.n - 2, 0, 0,
                            EntryPoint.CALL));
                    break;
                case RESUME2:
                    context.f2 = return_;
                    return_ = context.f1 + context.f2;
                    stack.pop();
                    break;
            }
        }
        return return_;
    }
}