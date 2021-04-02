# Twitchbot

<!-- TABLE OF CONTENTS -->
## Table of Contents

1. [About The Project](#About)
    - [Build](###Build)
2. [Getting Started](##Getting-started)
    - [Prerequisites](###Prerequisites)
    - [Dependencies](###Dependencies)
3. [Usage](##Usage)
    - [Compilation](###Compilation)
    - [Running](###Running)
4. [Roadmap](##Roadmap)
5. [Contributing](##Contributing)
6. [License](##License)
7. [Contact](##Contact)

## About

Making a general purpose twitch chat bot.

### Build

## Getting started

### Prerequisites

### Dependencies

This bot is dependent on having [libsockpp](https://github.com/fpagliughi/sockpp), [libasync](https://github.com/managarm/libasync) and [frigg](https://github.com/managarm/frigg) installed. You can install libsockpp from your package manager if available, or alternatively compile it from source. For frigg and libasync one can copy the folders with the headers to `/usr/include`. To build the bot, `meson` and `ninja` are required as well, install these from your package manager.

## Usage

### Compilation

To compile this project, run the following commands in order:

```bash
mkdir build ; cd build
meson ..
ninja
```

### Running
