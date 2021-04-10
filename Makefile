all: clean_concordo_exec channel_class message_class server_class text_channel_class voice_channel_class user_class system_class methods main concordo clean

channel_class: modules/channel_class.cpp
	g++ -Wall -c modules/channel_class.cpp -fsanitize=address -g

message_class: modules/message_class.cpp
	g++ -Wall -c modules/message_class.cpp -fsanitize=address -g

server_class: modules/server_class.cpp
	g++ -Wall -c modules/server_class.cpp -fsanitize=address -g

text_channel_class: modules/text_channel_class.cpp
	g++ -Wall -c modules/text_channel_class.cpp -fsanitize=address -g

voice_channel_class: modules/voice_channel_class.cpp
	g++ -Wall -c modules/voice_channel_class.cpp -fsanitize=address -g

user_class: modules/user_class.cpp
	g++ -Wall -c modules/user_class.cpp -fsanitize=address -g

system_class: modules/system_class.cpp
	g++ -Wall -c modules/system_class.cpp -fsanitize=address -g

methods: modules/methods.cpp
	g++ -Wall -c modules/methods.cpp -fsanitize=address -g

main: main.cpp
	g++ -Wall -c main.cpp -fsanitize=address -g

concordo:
	g++ channel_class.o message_class.o server_class.o text_channel_class.o voice_channel_class.o user_class.o system_class.o methods.o main.o -o concordo -fsanitize=address -static-libasan

clean_concordo_exec:
	rm -f concordo

clean:
	rm -f channel_class.o message_class.o server_class.o text_channel_class.o voice_channel_class.o user_class.o system_class.o methods.o main.o