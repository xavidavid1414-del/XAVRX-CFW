#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
STAGE="$ROOT/build/sd-package"
OUT="$ROOT/build/xavrx-sd-layout.zip"

rm -rf "$STAGE"
mkdir -p "$STAGE"
cp -a "$ROOT/distribution/sd-root/." "$STAGE/"
cp "$ROOT/distribution/README.txt" "$STAGE/README-XAVRX.txt"

mkdir -p "$(dirname "$OUT")"
(
  cd "$STAGE"
  zip -qr "$OUT" .
)

echo "Created: $OUT"
