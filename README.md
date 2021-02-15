# Learning Parallelization

This repository searves the dual purpose of being a place for me to learn and explore with HPC and parallelization of computer programs and also for a utility to give to others so that they can follow along and learn what I have learned faster than I have.

## Goals and Audience

Obviously the audience for a project like this is gonna need to have some experience, specifically in a compiled language like C, C++ or Fortran. All code is in C because I feel the most comfortable in it and it has a heavy presence in the HPC and scientific commputing community.

Prerequisites:

- Experience with a compiled language like [C, C++, or Fortran](https://inst.eecs.berkeley.edu/~cs61c/sp10/lec/C/C_Crash_Course.pdfF)
- Access to a [C compiler]("https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-160")
- Familiarity with [matrix computing and linear algebra]("https://bkenkel.com/pdaps/matrix.html")

The sources provided above are pretty good, but not necessarily built around HPC and scientific computing. The ideas presented in all of them should be enough to get up and running with HPC, but without prior experience, you're really gonna be fighting an uphill battle.

## Introduction to HPC

I will be using the introduction to HPC that is [written by someone else]("http://www.shodor.org/media/content/petascale/materials/UPModules/beginnersGuideHPC/moduleDocument_pdf.pdf") for time's sake:

> High performance and parallel computing is a broad subject, and our presentation is brief and given from a practitioner’s point of view. More recent developments, such as programming for multicore computers, cell computers, and field–programmable gate accelerators, are discussed in journals and magazines, with a short discussion at the end. By definition, supercomputers are the fastest and most powerful computers available, and at present the term refers to machines with hundreds of thousands of processors. They are the superstars of the high–performance class of computers. Personal computers (PCs) small enough in size and cost to be used by an individual, yet powerful enough for advanced scientific and engineering applications, can also be high–performance computers. We define high–performance computers as machines with a good balance among the following major elements:
>
> - Multi-staged (pipelined) functional units
> - Multiple central processing units (CPUs) (parallel machines)
> - Multiple cores
> - Fast central registers
> - Very large, fast memories
> - Very fast communication among functional units
> - Vector, video, or array processors
> - Software that integrates the above effectively
>
> As a simple example, it makes little sense to have a CPU of incredibly high speed coupled to a memory system and software that cannot keep up with it.

The rest of the document that this is taken from is super good. Go read it, really.

Also, the first few exercises in this are taken from the same paper as the introduction.

## Introduction to Parallel Computing

The first major concept that you need to understand before you can move forward in HPC programming is scaling. Scaling is the way that a program uses resources relative to the amount of resources that are avaiable. A program that cannot be run on multiple cores or threads at a time is useless in HPC. A program that can run on multiple cores or threads, but isn't any faster that it was when it was running on a single core is just as useless. When writing HPC programs, the goal is to write programs that can pass information between nodes so that each node can perform a portion of the calcualtion without other nodes having to wait for it to complete. That way, when you add more cores to the system, the program runs faster.
This is the basic concept behind scaling.

### Scaling Exercise

First a program that will not be sacable regardless of the
