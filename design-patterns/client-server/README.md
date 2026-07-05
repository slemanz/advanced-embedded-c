# Client-Server Pattern

## Abstract

The main idea is to divide an application into two main components: the client and the server.
Clients are responsible for interacting with the user and sending requests to the server,
while servers handle the processing of those requests and manage shared resources or services. 

## Problem

The pattern addresses the problem of how to distribute the workload and
responsibilities of an application, particularly when dealing with user interfaces, data
management, and complex computations. It allows for separating the user interface (client)
from the underlying business logic and data storage (server), enabling better scalability,
maintainability, and resource utilization. 

## Pattern Structure

- **Client:** A client application that requests services or resources from a server.
Clients can be user interfaces or other software components that need to access data or functionality
provided by the server.

- **Server:** A server application that provides services or resources to clients. Servers can
handle tasks like data storage, processing requests, and managing access to shared resources.

## Implementation Example

**[main.c](app/Src/main.c)**

**[ECG_Module.c](app/Src/ECG_Module.c)**

- **[systemManager.c](app/Src/systemManager.c)**
- **[arrythmiaDetector.c](app/Src/arrythmiaDetector.c)**
- **[QSRDetector.c](app/Src/QRSDetector.c)**
- **[histogramDisplay.c](app/Src/histogramDisplay.c)**

**[TMDQueue.c](app/Src/TMDQueue.c)**




