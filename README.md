# Twitchbot

## Table of Contents

1. [About The Project](#About)
    - [Status](#Status)
2. [Getting Started](#Getting-started)
    - [Prerequisites](#Prerequisites)
    - [Dependencies](#Dependencies)
3. [Usage](#Usage)
    - [Compilation](#Compilation)
    - [Running](#Running)
4. [Release History](#Release-History)
5. [Roadmap](#Roadmap)
6. [Contributing](#Contributing)
7. [License](#License)
8. [Contact](#Contact)

## About

There are many excisting great twitchbots, like Nightbot, streamelements and Streamlabs. However, I did not like any of those in particular so I decided to make my own bot. I wanted it to be fast in processing commands so that is why it is made in C++ and with the addition of asynchronous processing of messages. You can either run this on your own PC or server, or you could ask me to run it for you as it is build to connect and handle multiple messages.

### Status

This bot, when its run by me, has three versions: first we have a stable version, second we have a beta version with new not extensively tested features and last we have a dev build, this is basically an alpha build that has not been tested yet and changes a lot. Below this you can check the current build statusses of all these builds.

| Version        | Build status        |
| ------------- |:-------------:|
| **Master**     | [![Status Stable](http://vps.noahknegt.com:8050/api/projects/status/g327ndh0mqvkugv5/branch/master?svg=true)](http://vps.noahknegt.com:8050/project/AppVeyor/twitchbot/branch/master) |
| **Beta**     | [![Status Beta](http://vps.noahknegt.com:8050/api/projects/status/g327ndh0mqvkugv5/branch/Beta-Releases?svg=true)](http://vps.noahknegt.com:8050/project/AppVeyor/twitchbot/branch/Beta-Releases)      |
| **Dev** | [![Status Dev](http://vps.noahknegt.com:8050/api/projects/status/g327ndh0mqvkugv5/branch/Development?svg=true)](http://vps.noahknegt.com:8050/project/AppVeyor/twitchbot/branch/Development)     |

## Getting started

### Prerequisites

To start using this project for your own you can either download a prebuild version from the github [releases](https://github.com/Westlanderz/Twitchbot/releases) or [compile](#Compilation) it from source. To be able to run the program you need to have installed all the [dependencies](#Dependencies). It is tested on Linux so its able to run on that, but its not sure if it runs on Windows, so it is easier if you have a server or pc that runs Linux or run it in a VM.

### Dependencies

This bot is dependent on having [libsockpp](https://github.com/fpagliughi/sockpp), [libasync](https://github.com/managarm/libasync) and [frigg](https://github.com/managarm/frigg) installed. You can install libsockpp from your package manager if available, or alternatively compile it from source. For frigg and libasync one can copy the folders with the headers to `/usr/include`. To build the bot, `meson` and `ninja` are required as well, install these from your package manager.

## Usage

As stated in the [prerequisites](#Prerequisites) section you can use this bot by compling it from source or download it. Under this section we listed the steps needed to compile it from source.

### Compilation

To compile this project, run the following commands in order:

```bash
git clone https://github.com/Westlanderz/Twitchbot
cd Twitchbot
mkdir build ; cd build
meson ..
ninja
```

### Running

Once you have downloaded or compiled the bot, complete the following steps to run the bot:

1. ` mkdir files ; cd files `
2. ` mkdir config ; cd config `
3. ` touch config.txt `
4. Get your twitch oauth code from [here](https://twitchapps.com/tmi/), if it does not work check this [guide](https://dev.twitch.tv/docs/authentication)
5. Copy this key into the ` config.txt ` file.
6. ` nano channels.txt ` and on each line typeout the channel you want the bot to connect to.
7. ` cd ../.. `
8. ` mkdir build `
9. ` mv twitchbot build/ `
10. ` ./twitchbot `

## Release History

- v1.0.0 First stable release
  - Bot can join a channel
  - Bot can send responses to commands
  - Bot compiled by running make
- v1.1.0 Multichannel release
  - Bot is able to join multiple channels
  - Multiple channels can be listed in a file
  - No recompiling for a channel change
- v1.2.0 Timers
  - Added timed messages
  - Ability to add timers to a channel
- v1.2.1 Edittable Timers
  - Ability to edit excisting timers on a channel
- v1.2.2 Finalised Timers
  - You can now remove timers from a command
- v1.2.3 Timer update
  - Channels can now list their timers by name

## Roadmap

Nothing on the ROADMAP at this given moment, if you would like a feature to be added either fill in a feature request [here](https://github.com/Westlanderz/Twitchbot/issues/new/choose) or follow the steps [in the section below](#Contributing).

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (` git checkout -b feature/AmazingFeature `)
3. Commit your Changes (` git commit -m 'Add some AmazingFeature' `)
4. Push to the Branch (` git push origin feature/AmazingFeature `)
5. Open a Pull Request

## License

Distributed under the GPL-3.0 License. See `LICENSE` for more information.

## Contact

Noah Knegt - [@SenpaiR6](https://twitter.com/SenpaiR6) - admin@noahknegt.com

Project Link: [https://github.com/Westlanderz/Twitchbot](https://github.com/Westlanderz/Twitchbot)
