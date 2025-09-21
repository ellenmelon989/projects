# Final Project Proposal

## Group Members:

Jennifer Ye, Ellen Yu 

# Intentions:

A music streaming server like Spotify that can handle multiple users

# Intended usage:

Our music streaming server will allow clients to access, request, and control music playback. Multiple clients can add specific songs to a queue, and add or delete songs from a playlist. They can also create and view playlists, and view library. 

# Technical Details:

## topics covered in class
- server-client communication using sockets
- fork/exec processes to handle multiple client requests
- file handling to store music library information
- signals as shortcuts (skip song, create playlist, etc.)
- shared memory to correctly store playlists between processes
- semaphores to ensure synchronized shared memory

## project breakdown and responsibilities
### Jennifer
- file handling
- audio control
- socket implementation
- user features (requests, shuffle, playlists)
- signals
### Ellen
- server/client
- fork/exec
- signals
- user features (add, delete, playback)
- shared memory
- semaphores

## algorithms
- manage multiple client requests
- search song from library
- play, pause, stop song playback
- error handling

## data structures
- array of linked lists (music library)
- linked list of songs (playlists)
- individual user sessions (client interactions with server)
- buffer data (audio during streaming)
- shared memory (playlists, count)

# Intended pacing:

Jan 3 - proposal 
Jan 5 - implementing file handling to be able to play songs
Jan 8 - signals and new functions for users (ex: playing song, skipping song, playlists)
Jan 10 - adding client/server connections
Jan 12/15 - allowing multiple clients to use 
Jan 15 - polishing
Jan 16 - due
