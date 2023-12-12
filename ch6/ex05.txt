// tjdwill
// 12 December 2023
// Exercise 6.5
// @task:
//     Add the article the to the “English” grammar in §6.4.1, so that it can describe sentences such as “The birds fly but the fish swim.”

// From information regarding noun phrases: https://en.wikipedia.org/wiki/Noun_phrase

Sentence:
    NounPhrase Verb
    Noun Verb
    Sentence Conjunction Sentence
Conjunction:
    "and"
    "or"
    "but"
NounPhrase:
    Article Noun
Noun:
    "birds"
    "fish"
    "C++"
Verb:
    "rules"
    "fly"
    "swim"
Article:
    "the"
    "The"
    "A"
    "a"
    "An"
    "an"
/* 
    Check:
    We are attempting to see if the above sentence is valid. A valid sentence is either a NounPhrase and a Verb, A Noun and a Verb, or a Sentence followed by a Conjunction and another Sentence.
    "The" is neither a Noun nor a Sentence, but it is an Article. The following word, "birds" is a Noun. Together, the two form a NounPhrase. A NounPhrase followed by a Verb is a Sentence, so 
    "The birds fly" is a Sentence. This Sentence is followed by "but", which is a Conjunction, and "the fish swim" which is a Sentence via the same NounPhrase + Verb reasoning. Therefore, 
    "The birds fly but the fish swim" is a Sentence + Conjunction + Sentence which is indeed a Sentence as desired.
*/
