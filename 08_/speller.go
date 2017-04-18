package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
	"time"
	"unicode"
)

const (
	STANDART_DICTIONARY = "dictionaries/large"
	STANDART_TEXT       = "texts/austinpowers.txt"
)

var (
	mispelledWords []string
)

//===============================================
//============ CALCULATE & PRINT TIME  ==========
//===============================================
func timeKeeper(start time.Time, name string) {

	timePassed := time.Since(start)
	fmt.Printf("~ TIME IN %s => %s\n", name, timePassed)
}

//===============================================
//=========== LOADING TEXT INTO STRING  =========
//===============================================
func loadFile(filename string) string {

	defer timeKeeper(time.Now(), "READ FROM FILE : "+filename)
	content, err := ioutil.ReadFile(filename)
	if err != nil {
		panic(err)
	}
	return strings.ToLower(string(content))
}

//===============================================
//============= LOADING WORDS TO MAP  ===========
//===============================================
func makeDictionaryMap(inputText string) (map[string]string, int) {

	defer timeKeeper(time.Now(), "MAKE DICTIONARY")
	wordsInDictionary := 0
	wordsMap := make(map[string]string)         // initialize Map for Dictionary
	tempSlice := strings.Split(inputText, "\n") // split strings to Slice of words
	for i := range tempSlice {
		word := strings.Trim(tempSlice[i], "\r")
		wordsMap[word] = word // save words to Map
		wordsInDictionary++
	}
	return wordsMap, wordsInDictionary
}

//===============================================
//============= SPLIT WORDS FROM TEXT ===========
//===============================================
func splitWordsFromText(text string) ([]string, int) {

	wordsInText := 0
	var words []string
	word := ""
	for _, value := range text {
		if unicode.IsLetter(value) || (value == '\'' && len(word) > 0) {
			word += string(value)
		} else if unicode.IsDigit(value) {
			word = ""
		} else if len(word) > 0 {
			words = append(words, word)
			word = ""
			wordsInText++
		}
	}
	return words, wordsInText
}

//===============================================
//========== CHECK WORD IN DICTIONARY ===========
//===============================================
func checkWord(word string, workStream chan bool, dictionary map[string]string) {
	if dictionary[word] != word {
		mispelledWords = append(mispelledWords, word)
		workStream <- true
	} else {
		workStream <- false
	}
}

//===============================================
//============ MISPELLINGS FUNCTION =============
//===============================================
func getMisspellings(words []string, dictionary map[string]string) int {

	defer timeKeeper(time.Now(), "MISSPELLINGS WORDS")
	misspellings := 0
	workStream := make(chan bool)
	for _, word := range words {
		go checkWord(word, workStream, dictionary)
	}
	for range words {
		if <-workStream {
			misspellings++
		}
	}
	close(workStream)
	return misspellings
}

//===============================================
//========== GETTING PROGRAM PARMETERS ==========
//===============================================
func getParams() (string, string) {

	if len(os.Args) > 3 {

		panic("Usage: speller [dictionary] text")

	} else if len(os.Args) == 3 {

		return os.Args[1], os.Args[2]

	} else if len(os.Args) == 2 {

		return STANDART_DICTIONARY, os.Args[1]

	} else {

		return STANDART_DICTIONARY, STANDART_TEXT
	}
}

//***********************************************
//********************* MAIN ********************
//***********************************************

func main() {

	defer timeKeeper(time.Now(), "TOTAL")

	fileDictionary, fileText := getParams()

	dictionaryMap, wordsInDictionary := makeDictionaryMap(loadFile(fileDictionary))

	wordsArray, wordsInText := splitWordsFromText(loadFile(fileText))

	fmt.Println("~ WORDS IN DICTIONARY : ", wordsInDictionary)
	fmt.Println("~ WORDS IN TEXT : ", wordsInText)
	fmt.Println("~ WORDS MISSPELLED : ", getMisspellings(wordsArray, dictionaryMap))
	fmt.Println("~ MISSPELLED WORDS :", mispelledWords)

	// fmt.Println("========dictionary========")
	// j := 0
	// for i, value := range dictionaryMap {
	// 	j++
	// 	if j < 5 {
	// 		fmt.Printf("%v - %v |%q|\n", j, i, strings.Trim(value, "\r"))
	// 	}
	// }

	// fmt.Println("========text========")
	// for i, value := range wordsArray {
	// 	if i < 5 {
	// 		fmt.Printf("%v |%q|\n", i, strings.Trim(value, " "))
	// 	}
	// }
	// slovo := "titiZ"
	// fmt.Println(slovo, " =>", dictionaryMap[slovo], "|")
	// slovo = "total"
	// fmt.Println(slovo, " =>", dictionaryMap[slovo], "|")

}
