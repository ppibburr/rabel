Man oh man....

Allen Bradley sure likes to re-invent the wheel seemingly...

As I guess I should have expected, AB has made things different on the SLC's
versus the PLC-5's.  Whereas the PLC-5 has it's memory divided up into
"sections", the SLC appears to have no clear analogy.  Hense, the
read_section_size stuff does not appear to work with the SLC.  I am
researching more on this as they may have used different section numbers.

Why, oh why can't AB just use the same old proven technology over and over
again, like , oh, say --- Modicon.  There is a LOT to be said about not
changing the way things should work from platform to platform.  Sure, you
are free to add/expand features as new technology/demands are uncovered. 
However, unlike AB, Modicon's register read command has been the same
through at least 5 Platform revisions.

Oh well, enough of my whining...

This release basically gets the SLC register reading/writing working. 
Everything basic appears to work - in other words, reading/writing data
registers including floating point.  Since the SLC doesn't have sections in
the same sense as the PLC-5, I have no idea about the ability to read rung
data - yet.  I am working on it.  Don't know when/if it will get done.

What to expect in the next release - a basic rung reader.  Nothing fancy,
just the ability to print out the text of a run on the screen.  I would also
expect to see uploads (for the PLC-5 anyhow) working.  Note that the upload
process as documented by AB in the DF1 book will work but will give you a
useless backup unless that data is restored to the exact same
revision/model/series of PLC-5.  I have figured out how to do a "logical
backup" of a processor.  A logical backup allows you to do such things as
backup only certain sections of the PLC (like saving off the ladder only
with a who-cares attitude towards the rest of the data), and what not.  A
logical platform also allows you to migrate your program to other PLC-5
platforms (from a 5/20 to a 5/80 and what not).

These will take a bit to figure out.  In the meanwhile, if you encounter
anything that resembles a bug in this stuff, let me know and I'll fix it as
soon as I can.

Ron Gage - Saginaw, MI
(rongage@att.net)
