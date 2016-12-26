#!/bin/bash

TESTSTRING='justlinuxisthebestplaceabcdefghijkl'

if $( echo $TESTSTRING | grep --quiet 'justlinuxisthebestplaceabcdefghijkl' )
then
	echo true 'justlinuxisthebestplaceabcdefghijkl'
fi

if $( echo $TESTSTRING | grep --quiet 'oby' )
then
	echo true 'oby'
fi

