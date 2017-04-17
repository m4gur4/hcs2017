package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

const (
	ALPABET_LENGTH = 26
)

var (
	letterBigA   = byte('A')
	letterBigZ   = byte('Z')
	letterSmallA = byte('a')
	letterSmallZ = byte('z')
)

func isAlpha(letter byte) bool {

	if (letter < letterBigA) || (letter > letterSmallZ) {
		return false
	} else if (letter > letterBigZ) && (letter < letterSmallA) {
		return false
	}
	return true
}

func getInput() string {

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("plaintext: ")
	text, _ := reader.ReadString('\n')
	return text
}

func toUpp(char byte) byte {

	str := string(char)
	strings.ToUpper(str)
	rezult := []byte(str)
	return rezult[0]
}

func shiftChar(letter byte, k byte) byte {

	if isAlpha(letter) {
		if letter >= letterSmallA {
			return (((letter - letterSmallA) + k) % ALPABET_LENGTH) + letterSmallA
		} else if letter >= letterBigA {
			return (((letter - letterBigA) + toUpp(k)) % ALPABET_LENGTH) + letterBigA
		}
	}
	return letter
}

func encodeString(text string, k string) string {

	wordArray := []byte(text)
	wordKey := []byte(k)
	j := 0
	for i := 0; i < len(text); i++ {
		if isAlpha(wordArray[i]) {
			wordArray[i] = shiftChar(wordArray[i], wordKey[j])
			if j+1 < len(k)-1 {
				j++
			} else {
				j = 0
			}
		}
	}
	return string(wordArray)
}

func main() {

	if len(os.Args) == 2 {
		key := os.Args[1]
		text := strings.TrimRight(getInput(), "\n\r")
		result := encodeString(text, key)
		fmt.Println("ciphertext: ", result)
	} else {
		fmt.Println("Oops!  Usage: ./vigenere k")
	}

}
