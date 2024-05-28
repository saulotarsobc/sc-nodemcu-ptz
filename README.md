# SC - NodeMCU PTZ

<div align="center">
   <!-- <img alt="Build Status" src="https://img.shields.io/travis/saulotarsobc/scripts.svg"> -->
   <!-- <img alt="Test Coverage" src="https://img.shields.io/codecov/c/github/saulotarsobc/scripts.svg"> -->
   <img alt="Version" src="https://img.shields.io/github/v/release/saulotarsobc/sc-nodemcu-ptz.svg">
   <!-- <img alt="Downloads" src="https://img.shields.io/npm/dt/package-name.svg"> -->
   <img alt="License" src="https://img.shields.io/badge/License-MIT-yellow.svg">
   <img alt="Contributors" src="https://img.shields.io/github/contributors/saulotarsobc/sc-nodemcu-ptz.svg">
   <img alt="Last Commit" src="https://img.shields.io/github/last-commit/saulotarsobc/sc-nodemcu-ptz.svg">
   <img alt="Stars" src="https://img.shields.io/github/stars/saulotarsobc/sc-nodemcu-ptz.svg">
</div>

---

## Use

```sh
git clone https://github.com/saulotarsobc/sc-nodemcu-ptz.git;
cd sc-nodemcu-ptz;
npm install;
npm run dev;
```

## Help

- [Wireless javascript robotics with Johnny five and the ESP8266](https://dev.to/salted-bytes/wireless-javascript-robotics-with-johnny-five-and-the-esp8266-al3)
- [ESP8266 – NodeMCU PinOut](https://www.studiopieters.nl/esp8266-node-mcu-pinout/)

## NPM Commands

- **dev:** Builds the backend and then runs the application in development mode using Electron.

  ```json
  "dev": "npm run build:backend && electron . --dev"
  ```

  - `npm run build:backend`: Compiles the backend code using TypeScript.
  - `electron . --dev`: Starts the Electron application in development mode.

- **prebuild:** Cleans up the `build` and `dist` directories before building the project.

  ```json
  "prebuild": "rimraf build && rimraf dist"
  ```

  - `rimraf build`: Removes the `build` directory.
  - `rimraf dist`: Removes the `dist` directory.

- **build:** Builds both the frontend and the backend.

  ```json
  "build": "npm run build:frontend && npm run build:backend"
  ```

  - `npm run build:frontend`: Builds the frontend using Next.js.
  - `npm run build:backend`: Compiles the backend code using TypeScript.

- **build:frontend:** Compiles the frontend using Next.js.

  ```json
  "build:frontend": "next build frontend"
  ```

- **build:backend:** Compiles the backend using TypeScript.

  ```json
  "build:backend": "tsc -p backend"
  ```

- **postinstall:** Installs the application's dependencies using `electron-builder`.

  ```json
  "postinstall": "electron-builder install-app-deps"
  ```

- **dist:** Builds the project and then creates distribution artifacts using `electron-builder`.
  ```json
  "dist": "npm run build && electron-builder"
  ```
