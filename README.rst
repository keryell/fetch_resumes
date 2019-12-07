Fetching CV from Talemetry
==========================

Hiring platforms seem to target HR people and not technical hiring manager.

I just want the CV of the candidates and it does not seem possible... :-(

Talemetry can export the candidate list in CSV format with a column
with a link to the candidate page where you can access online the
information and in this page there is a link to downloaded the
candidate résumé.

This means that if you have 100 of candidates and 10 clicks + some
waiting time required to get each candidate résumé you end up with
1000 clicks and hours of web page baby-sitting... :-(

Not fancy for a computer scientist!

So why not having a tool to just download everything on your computer
and then you can look at the CV off-line?

This is this!

Some assumptions about the file format: it skips the first line that
should have the column description and assumes that the "," CSV file
has the URL in the last column, which is after the last ",".

To be fair, this small project is also an experiment about how modern
C++ can do a job where a shell script or Python could do the job. :-)
