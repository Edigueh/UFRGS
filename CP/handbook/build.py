#!/usr/bin/env python3
"""Generate handbook.tex from manifest.json.

ponytail: JSON not YAML — stdlib only, no pip install.
"""
import json
import sys
from pathlib import Path

HERE = Path(__file__).parent
REPO = HERE.parent
MANIFEST = HERE / "manifest.json"
OUT = HERE / "handbook.tex"

# Map manifest lang → listings language name.
LST_LANG = {"C++": "C++", "Python": "Python"}


def esc(s: str) -> str:
    """Escape LaTeX-special chars in blurb text (not code)."""
    return (
        s.replace("\\", r"\textbackslash{}")
        .replace("&", r"\&")
        .replace("%", r"\%")
        .replace("$", r"\$")
        .replace("#", r"\#")
        .replace("_", r"\_")
        .replace("{", r"\{")
        .replace("}", r"\}")
        .replace("~", r"\textasciitilde{}")
        .replace("^", r"\textasciicircum{}")
        .replace("<", r"\textless{}")
        .replace(">", r"\textgreater{}")
    )


PREAMBLE = r"""\documentclass[8pt,a4paper]{extarticle}
\usepackage[margin=8mm]{geometry}
\usepackage{multicol}
\usepackage{listings}
\usepackage{xcolor}
\usepackage{titlesec}
\usepackage[hidelinks]{hyperref}
\usepackage{needspace}

\setlength{\columnsep}{5mm}
\setlength{\parindent}{0pt}
\setlength{\parskip}{2pt}

\titleformat{\section}{\normalsize\bfseries}{\thesection}{0.4em}{}
\titlespacing*{\section}{0pt}{6pt}{2pt}
\titleformat{\subsection}{\small\bfseries}{}{0pt}{}
\titlespacing*{\subsection}{0pt}{4pt}{1pt}

\definecolor{cmt}{RGB}{110,110,110}
\definecolor{kw}{RGB}{0,60,140}
\definecolor{str}{RGB}{140,40,40}

\lstdefinestyle{cp}{
  basicstyle=\ttfamily\fontsize{7pt}{7.6pt}\selectfont,
  commentstyle=\color{cmt}\itshape,
  keywordstyle=\color{kw}\bfseries,
  stringstyle=\color{str},
  breaklines=true,
  breakatwhitespace=false,
  postbreak=\mbox{\textcolor{gray}{$\hookrightarrow$}\space},
  columns=fullflexible,
  keepspaces=true,
  showstringspaces=false,
  tabsize=2,
  frame=none,
  aboveskip=1pt,
  belowskip=1pt,
  xleftmargin=0pt,
  xrightmargin=0pt,
}
\lstset{style=cp}

% #1 title, #2 relative path, #3 strategy, #4 reuse, #5 language, #6 absolute file
\newcommand{\entry}[6]{%
  \needspace{4\baselineskip}%
  \subsection*{#1}%
  \addcontentsline{toc}{subsection}{#1}%
  {\scriptsize\ttfamily\color{gray} #2}\par
  {\footnotesize\textbf{Strategy:} #3\par\textbf{Reuse:} #4}\par\vspace{1pt}
  \lstinputlisting[language=#5]{#6}%
  \vspace{2pt}%
}

\title{\vspace{-8mm}\bfseries __TITLE__}
\author{}
\date{}
"""

DOC_HEAD = r"""\begin{document}
\maketitle\vspace{-6mm}
{\small\itshape __SUBTITLE__}\par\vspace{2pt}
\begin{multicols*}{2}
\tableofcontents
\vspace{4pt}
"""

DOC_TAIL = r"""\end{multicols*}
\end{document}
"""


def main() -> int:
    data = json.loads(MANIFEST.read_text())
    title = esc(data.get("title", "Handbook"))
    subtitle = esc(data.get("subtitle", ""))

    out = [
        PREAMBLE.replace("__TITLE__", title),
        DOC_HEAD.replace("__SUBTITLE__", subtitle),
    ]

    for cat in data["categories"]:
        cname = esc(cat["name"])
        out.append(f"\\section*{{{cname}}}\n")
        out.append(f"\\addcontentsline{{toc}}{{section}}{{{cname}}}\n")
        for e in cat["entries"]:
            abs_path = (REPO / e["path"]).resolve()
            assert abs_path.exists(), f"missing source: {abs_path}"
            lang = LST_LANG.get(e["lang"], e["lang"])
            out.append(
                "\\entry{%s}{%s}{%s}{%s}{%s}{%s}\n"
                % (
                    esc(e["title"]),
                    esc(e["path"]),
                    esc(e["strategy"]),
                    esc(e["reuse"]),
                    lang,
                    str(abs_path),
                )
            )

    notes = data.get("excluded_notes") or []
    if notes:
        out.append("\\section*{Excluded}\n")
        out.append("\\addcontentsline{toc}{section}{Excluded}\n")
        out.append("\\begin{footnotesize}\\begin{itemize}\\setlength\\itemsep{0pt}\n")
        for n in notes:
            out.append(f"\\item {esc(n)}\n")
        out.append("\\end{itemize}\\end{footnotesize}\n")

    out.append(DOC_TAIL)
    OUT.write_text("".join(out))
    print(f"wrote {OUT}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
