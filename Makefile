# all: create_build printer printer2 printer3 test
all: create_build main

create_build:
	mkdir -p build
	cd build
main:
	gcc -o  build/main main.c data_structures/form_data.c data_structures/settings.c data_structures/priority_queue.c utils/utilization_utils.c utils/beamerGenerator.c algorithms/earliest_deadline_first.c algorithms/least_laxity_first.c algorithms/rate_monotonic.c `pkg-config --cflags gtk+-3.0 --libs` -I. -Iutils -Idata_structures -Ialgorithms -lm