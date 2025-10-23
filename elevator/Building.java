import java.util.*;

public class Building {
    int maxfloor;
    int minfloor;

    public Building(int minFloor, int maxFloor) {
        this.minfloor = minFloor;
        this.maxfloor = maxFloor;
    }
    private boolean isValidFloor(int f) {
        return f >= minfloor && f <= maxfloor;
    }
    public static void main(String[] args) {
        Building b = new Building(-1, 10);
        Elevator e = new Elevator(1000, 10);
        System.out.println("Building created with min floor: " + b.minfloor + " and max floor: " + b.maxfloor);
        Scanner input = new Scanner(System.in); // create scanner object
        while (true){
            System.out.print("Press \"d\" when done. Otherwise what is the next task(s)? (in the form of \"pickup/dropoff\", floor number, passenger count) (if there are multiple requests, separate each with semicolon): ");
            String ans = input.nextLine();  
            if (ans.equalsIgnoreCase("d")){
                System.out.println("Exiting.");
                break;
            }
            if (ans.contains(";")){
                String[] requests = ans.split("; "); // split by semicolon
                for (String req : requests){
                    String[] parts = req.split(", "); // split by comma
                    if (parts.length != 3) {
                        System.out.println("Invalid input format in request: " + req + ". Please use: action, floor number, passenger count");
                        continue;
                    }
                    String action = parts[0];
                    int floornum;
                    int passcount;
                    try {
                        floornum = Integer.parseInt(parts[1]);
                        passcount = Integer.parseInt(parts[2]);
                    } catch (NumberFormatException ex) {
                        System.out.println("Floor number and passenger count must be integers in request: " + req);
                        continue;
                    }
                    if (!b.isValidFloor(floornum)) {
                        System.out.println("Floor " + floornum + " is not valid.");
                        continue;
                    }
                    if (action.equalsIgnoreCase("pickup")) {
                        e.pressfloor(floornum, passcount);
                    } else if (action.equalsIgnoreCase("dropoff")) {
                        e.pressfloor(floornum, -passcount);//will this cause issue with double neg?
                    } else {
                        System.out.println("Invalid action in request: " + req + ". Please use \"pickup\" or \"dropoff\".");
                        continue;
                    }
                }
                e.move(e.floorreqs);
                
            }
            else{
                String[] parts = ans.split(", "); // split by comma
                if (parts.length != 3) {
                    System.out.println("Invalid input format. Please use: action, floor number, passenger count");
                    continue;
                }
                else{
                    String action = parts[0];
                    int floornum;
                    int passcount;
                    try {
                        floornum = Integer.parseInt(parts[1]);
                        passcount = Integer.parseInt(parts[2]);
                    } catch (NumberFormatException ex) {
                        System.out.println("Floor number and passenger count must be integers.");
                        continue;
                    }
                    if (!b.isValidFloor(floornum)) {
                        System.out.println("Floor " + floornum + " is not valid.");
                        continue;
                    }
                    if (action.equalsIgnoreCase("pickup")) {
                        // e.pickup(passcount, floornum);
                        e.pressfloor(floornum, passcount);
                        e.move(e.floorreqs);
                    } else if (action.equalsIgnoreCase("dropoff")) {
                        // e.dropoff(passcount, floornum);
                        e.pressfloor(floornum, -passcount);
                        e.move(e.floorreqs);
                    } else {
                        System.out.println("Invalid action. Please use \"pickup\" or \"dropoff\".");
                        continue;
                    }
                }
            }
        }
        input.close();

    }
}
