esMonitorPC_VS: main.o procedure.o monitor_signal_continue.o
	gcc -o esMonitorPC_VS main.o procedure.o monitor_signal_continue.o

main.o: main.c procedure.h
	gcc -o main.o -c main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

monitor_signal_continue.o: monitor_signal_continue.c monitor_signal_continue.h
	gcc -o monitor_signal_continue.o -c monitor_signal_continue.c

clean:
	rm -f *.o
	rm -f esMonitorPC_VS
