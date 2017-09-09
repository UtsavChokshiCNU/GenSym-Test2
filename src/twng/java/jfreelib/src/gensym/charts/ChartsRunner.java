package gensym.charts;

/**
 * Main class
 */
public class ChartsRunner {
    /**
     * Application main routine
     * @param args aplication arguments
     */
    public static void main(String[] args) {
        System.out.println("JFree chart lib");
        if (args.length == 1) {
            try {
                ChartServer.doWork(Integer.valueOf(args[0]), 120000); // timeout = 2 minutes
                System.exit(0);
            } catch (NumberFormatException e) {
                String errorMsg = "Invalid server port parameter: " + args[0] + ". Should be numeric.";
                System.out.println(errorMsg);
            }
        } else {
            String errorMsg = "Error. Application should be ran with one parameter (server port).";
            System.out.println(errorMsg);
        }
    }
}
