package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
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

func shiftChar(letter byte, k byte) byte {

	if isAlpha(letter) {
		if letter >= letterSmallA {
			return (((letter - letterSmallA) + k) % ALPABET_LENGTH) + letterSmallA
		} else if letter >= letterBigA {
			return (((letter - letterBigA) + k) % ALPABET_LENGTH) + letterBigA
		}
	}
	return letter
}

func encodeString(text string, k int) string {

	wordArray := []byte(text)
	for i := 0; i < len(text); i++ {
		if isAlpha(wordArray[i]) {
			wordArray[i] = shiftChar(wordArray[i], byte(k))
		}
	}
	return string(wordArray)
}

func main() {

	if len(os.Args) == 2 {
		k, _ := strconv.Atoi(os.Args[1])
		text := strings.TrimRight(getInput(), "\n\r")
		result := encodeString(text, k)
		fmt.Println("ciphertext: ", result)
	} else {
		fmt.Println("Oops!  Usage: ./caesar k")
	}

}
