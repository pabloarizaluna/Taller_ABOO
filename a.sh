#!/bin/bash

input="/home/amodelaweb/Documents/dics/dics2.txt"
unset n
while IFS= read -r var
	do
  		#echo "$var"
  		IFS=',' tokens=( $var )
		#echo ${tokens[*]}
		#echo ${#tokens[@]}
		if [ ${#tokens[@]} == 2 ]; then
			#var=${tokens[1]//[[:blank:]]/}
			var=${tokens[1]//[[:blank:]]/}
			max=${#var}
			var=${tokens[0]//[[:blank:]]/}
			i=0
			max=$((max-1))
			while [ $max -ge $i ]
			do
				if [ ${#var} -gt 0 ]
				then
					var=${var: :-1}
				fi
				i=$((i+1))
				#echo ${var}
			done

			var=$var${tokens[1]//[[:blank:]]/}
			echo ${var} >> "$input"
			echo ${var}
			#echo ${var: :-1}
		fi
done < "$input"
