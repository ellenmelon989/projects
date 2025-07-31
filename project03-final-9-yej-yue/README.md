[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# music player

### jellen

Ellen Yu, Jennifer Ye
       
### Project Description:

Our project is meant to be a music player that can handle multiple clients. After the server and client connect, the server will inform the client and the client will input commands. The server forks for each client's command to allow proper running. We allocate memory for playlists and shared memory. Each client can then create playlists with this memory, add/delete songs from those playlists, view the playlists and overall library, and add songs to the queue. The changes made will be stored in shared memory that can be accessed in all processes. To ensure the shared memory is correct, we will use semaphores to have one process at a time. The clients can also exit the music player and control audio playback with signals: play, pause, skip, and rewind songs. 

At the moment, we can't get the shared memory to align correctly because it is not the same playlist data after forking finishes as inside the fork. We've reverted to a music player without server/client instead. 

UPDATED (WORKING ORIGINAL PROGRAM):
Our project is a multiclient music player that mimics spotify. Clients can create, modify, and view playlists as well as the queue. They can also play, skip, rewind, and pause songs. We use linked lists for the playlists and queue, and with client-server connection, the user can interactively alter them. The server contains instructions and the client inputs commands and song/playlist information for the server to process through socket connection. We allocate memory for the lists and work with audio (mp3) files to play music. In our program, we implement signals to exit the music player and find the songs' information, which is found with stat.
  
### Instructions:

To run the program, first make compile to compile each file. Then, run make server in one terminal and make client in another. The terminals should connect and in the client terminal, you can perform commands that will run in the server terminal. The instructions are printed into the terminal. 

Press 'm' to make a playlist, which will then ask for playlist name, base number of songs in playlist, and song names and artists. Pressing 'a' will add a song into a specific playlist, so the program will ask for a playlist name and song information. 'vplaylist' will ask for a playlist name for a specific playlist to print and 'vlib' will print out the entire music library, which shows you available songs to put into playlists or play. The 'd' command will delete a playlist or song, so you must tell the program which one you're deleting when prompted and the playlist/song info. 

To exit, press ctrl+c in each terminal. 

UPDATED (WORKING ORIGINAL PROGRAM) - relatively same instructions:

To run the program, first make compile to compile each file. Then, run make server in one terminal and make client in another. The terminals should connect and in the client terminal, you can perform commands that will run in the server terminal. The instructions are printed into the terminal.
In the server/client program, the commands are:
- type 'm' to make a playlist, which will then ask for playlist name, base number of songs in playlist, and song names and artists
- type 'a' to add a song into a specific playlist, so the program will ask for a playlist name and song information. 
- type 'vplaylist' will ask for a playlist name for a specific playlist to print 
- type 'vlib' will print out the entire music library, which shows you available songs to put into playlists or play. 
- type 'd' command will delete a playlist or song, so you must tell the program whether you're deleting a playlist or song when prompted and the playlist/song info. 
- type 'play' to play a song
- type 'q' to add a song to the queue
- type 'v' to view the queue
- type 'c' to clear the queue

In the main.c program (without server/client connection):
- type 'vlib' to view the entire library of songs at your disposure
- type 'mplaylist' to make a new playlist
- type 'vplaylist' to view a specific playlist
- type 'add2playlist' to add to a specified playlist
- type 'deletefromplaylist' to specify a song to delete from a specific playlist
- type 'deleteplaylist' to delete a specific playlist
- type 'playsong' to specify a song to play out loud
- type 'add2queue' to add songs to play in a queue
- type 'vqueue' to view all the songs currently in the queue
- type 'playqueue' to play all the songs in the queue
- type 'clearqueue' to clear all the songs in the queue

bugs:
- can only play and interact with songs that we already put into the program 
- deleting a playlist after deleting all the songs will result in an error (double free)