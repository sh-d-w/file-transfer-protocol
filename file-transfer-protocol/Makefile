#                        __________________							   #
#                         S |-| - D - \/\/ 							   #
#                        ==================							   #
# 																	   #
#    	   Original code developed during 42.fr curriculum. 		   #
#  			  Project renamed and refactored for clarity.			   #
#              Created: 2017-07-16 by S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ				   #
# 																	   #
#    Copyright [2026] [S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ] under Apache 2.0 License	   #

SERVER=	server
CLIENT=	client

C_P=	src/client
S_P=	src/server

C_SRC=	$(C_P)/client.c $(C_P)/lib.c $(C_P)/shell.c $(C_P)/transfer.c
S_SRC=	$(S_P)/server.c $(S_P)/lib.c $(S_P)/shell.c $(S_P)/transfer.c

all:
	@rm -rf client server
	gcc -o client $(C_SRC)
	@cp client ../client
	gcc -o server $(S_SRC)

$(CLIENT):
	gcc -o $(CLIENT) $(C_SRC)

$(SERVER):
	gcc -o $(SERVER) $(S_SRC)

re:
	make all

clean:
	@rm -rf client
	@rm -rf server

fclean:
	@make clean
