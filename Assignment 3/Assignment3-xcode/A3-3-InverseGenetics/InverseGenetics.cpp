/* File: InverseGenetics.cpp
 *
 * A program that, given a sequence of amino acids, returns all possible
 * RNA strands that could encode that amino acid sequence.
 *
 *************************************************************************************************************
 * Set<> class implementation has conflict with Xcode linker with symbol visibility misfit stuff.
 * More, see //stackoverflow.com/questions/5285844/bad-codegen-pointer-diff-linker-error-with-xcode-4
 *************************************************************************************************************
 */
#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "foreach.h"
#include "simpio.h"

using namespace std;

/* Function: allRNAStrandsFor(string protein,
 *                            Map<char, Set<string> >& codons);
 * Usage: foreach (string rna in allRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, returns all possible RNA strands that could generate
 * that protein.
 */
Set<string> allRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

void recAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons, string oneRNAStrand, Set<string> & RNASet);



int main() {
	/* Load the codon map. */
	Map<char, Set<string> > codons = loadCodonMap();
	
	/* TODO: Add testing code here! */
    string protein = getLine("Enter the protein sequence: ");
    Set<string> RNAStrands = allRNAStrandsFor(protein, codons);
    foreach(string oneRNAStrand in RNAStrands) {
        cout << oneRNAStrand << endl;
    }
	return 0;
}

Set<string> allRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
	// TODO: Implement this function!
    Set<string> RNASet;
    recAllRNAStrandsFor(protein, codons, "", RNASet);
    return RNASet;
}

void recAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons, string oneRNAStrand, Set<string> & RNASet) {
    if (protein.empty()) {
        RNASet.add(oneRNAStrand);
        return;
    }
    char aminoAcid = protein[0];
    foreach(string codon in codons[aminoAcid]) {
        oneRNAStrand += codon;
        recAllRNAStrandsFor(protein.substr(1), codons, oneRNAStrand, RNASet);
        oneRNAStrand.erase(oneRNAStrand.size() - codon.size());
    }
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
	ifstream input("codons.txt");
	Map<char, Set<string> > result;
    
	/* The current codon / protein combination. */
	string codon;
	char protein;
	
	/* Continuously pull data from the file until all data has been
	 * read.  We did not cover this syntax in class, but it means
	 * "while reading a codon/protein pair succeeds, add the pair to
	 * the map."
	 */
	while (input >> codon >> protein) {
		result[protein] += codon;
	}
	
	return result;
}

