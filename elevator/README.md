## Running:
- compile both java files (javac *.java)
- run (java Building)
- input instructions in the format ("pickup/dropoff", desired floor, number of passengers to pickup/dropoff; task, floor, passenger; etc.) *please separate each input with ', ' and each set of instructions with '; '*
## Elevator features and assumptions:
- one elevator right now
- completes all tasks in one direction before heading in the other
- if same floor inputted multiple times in one instruction batch, elevator will group those all as if simultaneous and perform the net action
- start with no passengers inside elevator on ground floor (0), so the first thing the elevator will do is pickup no matter what
- assumes avg weight for each passenger

## Could Change:
- could make an elevator belong to a building explicitly
- could make it more complex with multiple of each - Thread
- obstruction sensor or holding the doors open/closed
- can allow commands to be implemented as the elevator is moving