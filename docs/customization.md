# XAVRX CFW — Customization and Splash Media

## Product requirement

XAVRX is planned to support user-customizable startup presentation and HOME Menu-style themes:

1. **Animated startup splash** — video playback during XAVRX startup, with an optional synchronized sound track.
2. **Static splash fallback** — image-only startup screen when video or audio cannot be initialized.
3. **Custom themes** — user-selected visual themes for the XAVRX interface, including backgrounds, colors, icons, and layout assets.
4. **Theme music and sounds** — optional background music and interface sound effects, independently switchable.
5. **Theme manager** — preview, select, enable/disable, and safely fall back to the default theme.

## Important distinction

A video splash is a planned XAVRX feature, not something the current diagnostic app can play. Full-motion video and synchronized audio require a media decoder, audio initialization, memory budgeting, frame timing, and a startup stage capable of presenting frames. The first implementation target should be playback after the XAVRX runtime has initialized. A pre-runtime boot animation is a separate later capability and must not delay or interfere with recovery.

## Proposed asset package

A future theme package will use a manifest and a small set of optional assets. The exact media container and codec will be selected only after testing what the 3DS hardware and available libraries can decode within memory and CPU limits.

Conceptual layout:

    /xavrx/themes/<theme-id>/theme.json
    /xavrx/themes/<theme-id>/background.bin
    /xavrx/themes/<theme-id>/icons/
    /xavrx/themes/<theme-id>/music/<audio-file>
    /xavrx/splashes/<splash-id>/manifest.json
    /xavrx/splashes/<splash-id>/video/<video-file>
    /xavrx/splashes/<splash-id>/audio/<audio-file>

These paths are a design proposal, not supported runtime paths yet.

## Compatibility and safety rules

- Missing or invalid media must fall back to the default static splash.
- Theme or media parsing must be bounded and reject malformed manifests.
- No theme package may contain executable code.
- User media must never be loaded from NAND or boot-critical locations.
- Audio must be optional and independently disableable.
- Provide a setting to skip the animation and boot directly to the interface.
- Keep a built-in default theme so a broken custom theme cannot prevent startup.
- Measure memory, CPU use, startup delay, and package size on real hardware before declaring compatibility.

## Implementation stages

- [x] Record the feature requirements and fallback behavior
- [ ] Define and validate a versioned theme manifest
- [ ] Add theme discovery and preview using read-only SD access
- [ ] Add static splash image support in the initialized runtime
- [ ] Evaluate a lightweight video decoder and supported formats
- [ ] Add synchronized optional audio playback
- [ ] Add theme music and interface sound support
- [ ] Evaluate pre-runtime video splash feasibility separately
- [ ] Verify performance and recovery behavior on New Nintendo 2DS XL

## Current status

This document records planned compatibility only. None of the video, splash audio, or theme-loading features are implemented yet.
