# get_unmapped
Find reads not mapped by srnaMapper.

## Get the code

Using `git`:

    git clone https://github.com/mzytnicki/get_unmapped.git
    cd get_unmapped

Or download *via* link https://github.com/mzytnicki/get_unmapped/archive/refs/heads/main.zip and uncompress.

## Compile the code

On Linux, type 

    g++ -O2 get_unmapped.cpp -o get_unmapped

(This should work with Clang too).
You should have the `get_unmapped` executable.

## Use `get_unmapped`

We suppose that you have the fastq file `file.fastq`, that you mapped with `srnaMapper` (or any other tool), in order to have `file.sam`.

In this case, you can type:

    get_unmapped file.sam file.fastq > file_unmapped.fastq

Using bash, you can still use a BAM file, and a compressed FASTQ file, using the following command:

    ./get_unmapped <( samtools view file.bam ) <( zcat file.fastq.gz ) > file_unmapped.fastq

## What `get_unmapped` does

This tools only retrieves the FASTQ sequences that are not present in the SAM file.

Specifically, if a read can be mapped several times, `srnaMapper` will output this read, but it will flag it as unmapped.
This tool, `get_unmapped`, will not retrieve these reads.
