# Car-management-and-maintenance-system
In this project, we designed a management system that allows adding, deleting and searching vehicle and maintenance records.

## Records used

### 1- Car Registry

1. Car_id: Car number.
1. Type: Vehicle type.
1. Color: The color of the car.
1. Owner_name: The name of the car owner.
1. Phone: The car owner's number.


### 2- Maintenance record
```
-Maintenance_number: Maintenance operation number.
-Car_id: The number of the car undergoing maintenance.
-Maintenance_date: The date of the maintenance operation.
-Typesnumber: The number of part types used.
-Pieces[100][100]: A binary array of integers containing in each column the number of the piece in the first line and the number used from this piece in the second line.
-Coast: The cost of maintenance without parts.
-Total_coast: The cost of maintenance with parts.
```

### 3- Piece record
```
-Piece_id: Part number.
-Price: The price of the piece.
-Linked List Record: Each node has a maintenance log and a pointer to the next node.
```

## Methods used
```
-Continue adding a car 
-Continue adding a maintenance operation
-Continue deleting a car record
-Continue searching for the owner's name and display all his car numbers
-Continue to view maintenance operations organized by car number
-View maintenance operations for a specific vehicle and calculate the cost
-Find the most used piece
-Track cars that have been serviced after a certain date
```
