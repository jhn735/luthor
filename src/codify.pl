#changes the code in luthor.cpp and luthor.h into a set of strings
	#separated by generated code.
sub codify {
	#the return value will be a set of strings
	my @retVal;
	#get the input file filename
	my $input_filename = shift;
	#open the file to be read;
	open input_file, "<", $input_filename 
		or die "$input_filename: $!";
	
	my $in_generated = 0;
	my $cur_string = "";
	#for each line in the file
		#replace every instance of newline and tab with
		# \\n\n and \t respectively
	#make sure to split the file in strings separated by generated code
	while(<input_file>){
		if(m/generated::start/){
			#we have reached the in generated section
			$in_generated = 1;
			#add the current line to the string and add it to retVal
				#this marks the end of the code piece
			#do the correct replacements
			s/\t/\\t/g;
			s/\n/\\n\\\n/g;
			#write the current line to the end of the current string
			$cur_string = $cur_string . $_;
			#add the current string to the array
			push(@retVal, $cur_string);
			#reset the current string;
			$cur_string = "";
		}else{ if(m/generated::end/){
			$in_generated = 0;	
		}}

		if(!$in_generated){
			#replace all quotes with their escape equivalences
			s/\"/\\\"/g;
			#replace all tabs with \t
			s/\t/\\t/g;
			#replace all newlines with '\n' and a '\'
				#followed by a newline
			s/\n/\\n\\\n/g;
			#add the current line to the current string
			$cur_string = $cur_string . $_;
		}
	}#end while(<input_file>)...
#close the file and return a value
	push(@retVal, $cur_string);
	close input_file;
return @retVal;
}

#open the output file
open code_file, ">", "include/code.h" or die "code.h: $!";
print code_file "#ifndef CODE_H \n#define CODE_H\n";

my @filenames = ('luthor.h', 'luthor.cpp');
my @paths = ('./include/', './');
#for each of the filenames
for my $index (0 .. $#filenames){
	my $filename = $filenames[$index];
	my $path = $paths[$index];
	#get the pieces of the file and save them to the code
	my @codePieces = codify($path . $filename);
	my $index = 0;
	#change the filename to all caps and replace the '.' with a '_'
	my $name = $filename;
	$name = (uc $name) . "_P_";
	$name =~ s/\./\_/g;

	foreach $cur_piece (@codePieces){		
		$index++;
		my $def = "\t#define " . $name . "$index " 
			. "\"" . "$cur_piece" . "\"\n";
		print code_file $def;
	}#end foreach $cur_piece (@codePieces)
}#end foreach $filename (@filenames)

#finish off the file
print code_file "#endif\n";
close code_file;
