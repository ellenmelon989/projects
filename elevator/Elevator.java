import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Deque;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Elevator {
    // movement up and down
    // door open and close
    // weight limit
    // choose floor
    // emergency stop
    // alarm system
    // travel time?

    int floor = 0; //start at ground 
    boolean emergency = false;
    int weightlimit; //pounds
    int capacity; //number of people
    int currweight = 0;
    int currpop = 0;
    int door = 0; //0 closed, 1 open
    int moving = 0; //0 not moving, 1 up, -1 down
    // boolean pickedup = false;
    // Deque<int[]> floorreqs = new ArrayDeque<>(); // floor, numpassengers
    ArrayList<int[]> floorreqs = new ArrayList<>(); // floor, numpassengers

    public Elevator(int wlimit, int maxcap) {
        this.weightlimit = wlimit;
        this.capacity = maxcap;
    }
    public void pressfloor(int f, int numpass){
        floorreqs.add(new int[]{f, numpass});
    }
    public void move(ArrayList<int[]> reqs){ //client/server? also. need to make sure pickup before dropoff
        if (emergency) {
            System.out.println("Cannot move, emergency stop activated");
            return;
        }
        if (door == 1) {
            System.out.println("Cannot move, doors are open");
            return;
        }
        if (reqs.isEmpty()) {
            System.out.println("No more floors pushed");
            return;
        }
        Map <Integer, Integer> reqmap = new HashMap<>();
        for (int[] r : reqs){
            reqmap.merge(r[0], r[1], Integer::sum);
        }
        // pickup first
        System.out.println("Current passengers: "+currpop);
        if (currpop ==0){
            int pickupfloor = Integer.MAX_VALUE;
            for (int f : reqmap.keySet()) {
                if (reqmap.get(f) > 0) {
                    if (Math.abs(f)<pickupfloor) {
                        pickupfloor = f;
                    }
                }
            }
            if (pickupfloor != Integer.MAX_VALUE){
                System.out.println("Picking up first on " + pickupfloor);
                try {
                    int floordiff = pickupfloor - floor;
                    System.out.println("Moving from floor " + floor + " to floor " + pickupfloor);
                    Thread.sleep(1000*Math.abs(floordiff)); // 1 second per floor
                    floor = pickupfloor;
                    System.out.println("Arrived at floor " + floor+". Opening door");
                    door = 1;
                    pickup(reqmap.get(pickupfloor), pickupfloor);
                    reqmap.remove(pickupfloor);
                    final int pfloor = pickupfloor;
                    reqs.removeIf(r -> r[0] == pfloor);
                    // pickedup = true;
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt(); // restore the interrupted status so others can see
                    System.err.println("Issue going to the floor, still on "+floor);
                    moving = 0;
                }
                // floor = pickupfloor;
            }
            else{
                System.out.println("Need to pick someone up first, can't drop off nonexistent passengers. Clearing requests");
                reqs.clear();
                return;
            }
        }

        if (reqmap.containsKey(floor)) {
            int numpass = reqmap.get(floor);
            System.out.println("Already on floor " + floor+ ". Servicing here first");
            door = 1;
            if (numpass < 0){
                System.out.println("Trying to drop off passengers at "+floor);
                dropoff(numpass, floor);
            }
            else if (numpass > 0){
                System.out.println("Trying to pick up passengers at "+floor);
                pickup(numpass, floor);
            }
            reqmap.remove(floor);
            reqs.removeIf(r -> r[0] == floor);
        }
        List<Integer> up = new ArrayList<>();
        List<Integer> down = new ArrayList<>();
        for (int f : reqmap.keySet()) {
            if (f > floor) up.add(f);
            else if (f < floor) down.add(f);
        }
        Collections.sort(up);                   
        down.sort(Collections.reverseOrder());     
        int dir = moving;
        if (up.isEmpty()) dir = -1;
        else if (down.isEmpty()) dir = 1;
        if (dir == 0) {
            if (Math.abs(up.get(0)-floor) <= Math.abs(down.get(0)-floor)) dir = 1;
            else dir = -1;
        } 
        if (dir==1){
            service(up, reqmap);
            service(down, reqmap);
        } else if (dir == -1){
            service(down, reqmap);
            service(up, reqmap);
        }
        moving = 0;
        door = 0;
        System.out.println("All requests served. Elevator idle on floor " + floor);
    }
    private void service(List<Integer> list, Map<Integer, Integer> rmap){
        if (list.isEmpty()) return;
        for (int newfloor : list){
            int floordiff = newfloor - floor;
            int numpass = rmap.get(newfloor);
            try {
                // moving = (int) Math.signum(floordiff);
                System.out.println("Moving from floor " + floor + " to floor " + newfloor);
                Thread.sleep(1000*Math.abs(floordiff)); // 1 second per floor
                floor = newfloor;
                System.out.println("Arrived at floor " + floor+". Opening door");
                door = 1;
                if (numpass < 0){
                    System.out.println("Trying to drop off passengers at "+newfloor);
                    moving = 0;
                    dropoff(numpass, newfloor);
                }
                else if (numpass > 0){
                    System.out.println("Trying to pick up up passengers at floor "+newfloor);
                    moving = 0;
                    pickup(numpass, newfloor);
                }
                rmap.remove(newfloor);
                floorreqs.removeIf(r -> r[0] == newfloor);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // restore the interrupted status so others can see
                System.err.println("Issue going to the floor, still on "+floor);
                moving = 0;
            }
        }
    }
    public void pickup(int numpassengers, int pfloor){
        // if (pfloor != floor) {
        //     System.out.println("Not on requested floor. Adding " + pfloor+" to requests");
        //     pressfloor(pfloor, numpassengers);
        //     return;
        // }
        door =1;
        if (door == 0) {
            System.out.println("Cannot pick up passengers, doors are closed");
            return;
        }
        if (moving != 0) {
            System.out.println("Cannot pick up passengers, elevator moving");
            return;
        }
        // door = 1; //open door
        if (currpop + numpassengers > capacity) {
            System.out.println("Cannot pick up these passengers, capacity exceeded");
            return;
        }
        if (currweight + (numpassengers * 150) > weightlimit) { //assuming avg weight 
            System.out.println("Cannot pick up these passengers, weight limit exceeded");
            return;
        }
        System.out.println("Picked up " + numpassengers + " passengers at floor " + floor);
        currpop += numpassengers;
        currweight += numpassengers * 150;
        System.out.println("Current passengers: "+currpop);
        try {
            Thread.sleep(2000); // 2 seconds to close door
            door = 0; 
            System.out.println("Doors closed");
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt(); // restore the interrupted status so others can see
            System.err.println("Door wasn't closed");
        }
    }
    public void dropoff(int numpassengers, int dfloor){
        if (dfloor != floor) {
            System.out.println("Not on requested floor. Adding " + dfloor+" to requests");
            if (numpassengers > 0) pressfloor(dfloor, -numpassengers);
            else pressfloor(dfloor, numpassengers);
            return;
        }
        door = 1;
        if (door == 0) {
            System.out.println("Cannot drop off passengers, doors are closed");
            return;
        }
        if (moving != 0) {
            System.out.println("Cannot drop off passengers, elevator moving");
            return;
        }
        if (Math.abs(numpassengers) > currpop) {
            System.out.println("Cannot drop off more passengers than currently in elevator");
            return;
        }
        // door = 1; //open door
        System.out.println("Dropped off " + Math.abs(numpassengers) + " passengers at floor " + floor);
        if (numpassengers > 0) currpop -= numpassengers;
        else currpop += numpassengers;
        currweight -= numpassengers * 150;
        System.out.println("Current passengers: "+currpop);
        try {
            Thread.sleep(2000); // 2 seconds to close door
            door = 0; 
            System.out.println("Doors closed");
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt(); // restore the interrupted status so others can see
            System.err.println("Door wasn't closed");
        }
    }
}

