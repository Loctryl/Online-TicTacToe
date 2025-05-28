# Online TicTacToe

## Context
This is a student project with a team of 4 people, during 2 weeks. (November 2023)
The goal was to learn about TCP/IP networking and threads architecture. The game is only used to illustrate the system behind.

## Technical part
There are 2 applications there : the server and the client. 

The server is here to make the connection between the 2 players (clients) by sending the data from one to an other and checking the state of the game. It also generate the website tracking every game currently played in the server.

The client is for the player. The first interface is to connect to the server with an IP address and a custom nickname. After logging, the player enters an empty room or joins with a slot. When the game is done, the player can stay in the room to start an other game or just leave it.
We use SFML 2.6 for rendering the interface in the client.

Each one support network communication on a different thread, and the website is also managed in a different thread in the server.

## Screenshots
- Client menu : 

![image](https://github.com/user-attachments/assets/530520da-106d-41e6-8066-59bf21ebd31b)

- Client view of the game : 

![image](https://github.com/user-attachments/assets/a8062d03-b090-47e5-adfb-0d0a8a8cf3f0)

- Website's game tracking : 

![image](https://github.com/user-attachments/assets/c72bf394-c434-4f8d-819e-62d3d75e0648)

- Server's request tracking : 

![image](https://github.com/user-attachments/assets/af81a753-4563-4125-b16c-576fd72bd1bd)

