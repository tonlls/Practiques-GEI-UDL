
test:
	for t in *.in; do ./aqueducte $$t > sortida; diff -q `basename $$t .in`.ans sortida; done
