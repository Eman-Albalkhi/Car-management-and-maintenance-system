# Car-management-and-maintenance-system
In this project, we designed a management system that allows adding, deleting and searching vehicle and maintenance records. The system involves using four different records and linking them together using a sequential list.

## Records used

### 1- Car Registry
-Car_id: Car number.
-Type: Vehicle type.
-Color: The color of the car.
-Owner_name: The name of the car owner.
-Phone: The car owner's number.

### 2- Maintenance record:
-Maintenance_number: Maintenance operation number.
-Car_id: The number of the car undergoing maintenance.
-Maintenance_date: The date of the maintenance operation.
-Typesnumber: The number of part types used.
-Pieces[100][100]: A binary array of integers containing in each column the number of the piece in the first line and the number used from this piece in the second line.
-Coast: The cost of maintenance without parts.
-Total_coast: The cost of maintenance with parts.

### 3- Piece record:
-Piece_id: Part number.
-Price: The price of the piece.
-Linked List Record: Each node has a maintenance log and a pointer to the next node.
