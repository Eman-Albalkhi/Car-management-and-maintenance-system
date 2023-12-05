# Car-management-and-maintenance-system
In this project, we designed a management system that allows adding, deleting and searching vehicle and maintenance records.

## Records used

#### - Car Registry

1. Car_id: Car number.
1. Type: Vehicle type.
1. Color: The color of the car.
1. Owner_name: The name of the car owner.
1. Phone: The car owner's number.


#### - Maintenance record
 1. Maintenance_number: Maintenance operation number.
1. Car_id: The number of the car undergoing maintenance.
1. Maintenance_date: The date of the maintenance operation.
1. Typesnumber: The number of part types used.
1. Pieces[100][100]: A binary array of integers containing in each column the number of the piece in the first line and the number used from this piece in the second line.
1. Cost: The cost of maintenance without parts.
1. Total_coast: The cost of maintenance with parts.


#### - Piece record

1. Piece_id: Part number.
1. Price: The price of the piece.
1. Linked List Record: Each node has a maintenance log and a pointer to the next node.


## Methods used

1. Continue adding a car 
1. Continue adding a maintenance operation
1. Continue deleting a car record
1. Continue searching for the owner's name and display all his car numbers
1. Continue to view maintenance operations organized by car number
1. View maintenance operations for a specific vehicle and calculate the cost
1. Find the most used piece
1. Track cars that have been serviced after a certain date

