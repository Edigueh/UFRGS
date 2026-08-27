#!/usr/bin/env bash
# Build handbook.pdf from manifest.json + repo sources.
# ponytail: pdflatex twice (TOC needs second pass), no latexmk dep.
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$HERE"

python3 build.py

if command -v tectonic >/dev/null 2>&1; then
  # Tectonic auto-fetches packages, single pass handles TOC via reruns.
  tectonic --keep-logs --outdir . handbook.tex
elif command -v pdflatex >/dev/null 2>&1; then
  pdflatex -interaction=nonstopmode -halt-on-error handbook.tex >build.log 2>&1
  pdflatex -interaction=nonstopmode -halt-on-error handbook.tex >build.log 2>&1
else
  cat >&2 <<'EOF'
error: no LaTeX engine found (need `tectonic` or `pdflatex`).

Fastest fix (no sudo, no admin password):
  brew install tectonic

Or install BasicTeX:
  brew install --cask basictex
  eval "$(/usr/libexec/path_helper)"
  sudo tlmgr install listings geometry multicol titlesec extsizes hyperref needspace
EOF
  exit 127
fi

# Move aux clutter out of sight; keep pdf and log.
mkdir -p .aux
mv -f handbook.aux handbook.toc handbook.out .aux/ 2>/dev/null || true

echo "ok: $(pwd)/handbook.pdf"
