int pin_pot1 = A0;
int pin_pot2 = A1;
//--------------------------------------
int pin_led = 11;
//--------------------------------------

#include <Fuzzy.h>
Fuzzy *fuzzy = new Fuzzy();

// FuzzyInput pH
FuzzySet *asam            = new FuzzySet(0, 0, 6, 6.5);
FuzzySet *netral          = new FuzzySet(6, 7, 8);
FuzzySet *basa            = new FuzzySet(7.5, 8, 14, 14);

// FuzzyInput DeltapH
FuzzySet *negatif          = new FuzzySet(-7, -7, -0.5, 0);
FuzzySet *netral           = new FuzzySet(-0.5, 0, 0.5);
FuzzySet *positif          = new FuzzySet(0, 0.5, 7, 7);

// FuzzyOutput hasil
FuzzySet *turunCepat          = new FuzzySet(-1023);
FuzzySet *turunLambat         = new FuzzySet(-700);
FuzzySet *berhenti            = new FuzzySet(0);
FuzzySet *naikLambat          = new FuzzySet(700);
FuzzySet *naikCepat           = new FuzzySet(1023);

void setup()
{
  //setting kecepatan data dalam bit persecond (baud) 115200bps
  Serial.begin(115200);
  pinMode(pin_led , OUTPUT);

  //--------------------------------------

  // FuzzyInput pH
  FuzzyInput *pH = new FuzzyInput(1);

  pH->addFuzzySet(asam);
  pH->addFuzzySet(netral);
  pH->addFuzzySet(basa);
  fuzzy->addFuzzyInput(pH);



  // FuzzyInput DeltapH
  FuzzyInput *DeltapH = new FuzzyInput(2);

  DeltapH->addFuzzySet(negatif);
  DeltapH->addFuzzySet(netral);
  DeltapH->addFuzzySet(positif);
  fuzzy->addFuzzyInput(DeltapH);



  // FuzzyOutput hasil
  FuzzyOutput *hasil = new FuzzyOutput(1);

  hasil->addFuzzySet(turunCepat);
  hasil->addFuzzySet(turunLambat);
  hasil->addFuzzySet(berhenti);
  hasil->addFuzzySet(naikLambat);
  hasil->addFuzzySet(naikCepat);
  fuzzy->addFuzzyOutput(hasil);
  //--------------------------------------






  // Membuat FuzzyRule////////////////////////////////////////////////////////////////// 1
  FuzzyRuleAntecedent *asam_positif = new FuzzyRuleAntecedent();
  asam_positif ->joinWithAND(asam, positif);

  FuzzyRuleConsequent *hasil_naikCepat = new FuzzyRuleConsequent();
  hasil_naikCepat->addOutput(naikCepat);

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, asam_positif, hasil_naikCepat);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 2
  FuzzyRuleAntecedent *asam_netral = new FuzzyRuleAntecedent();
  asam_netral->joinWithAND(asam, netral);

  FuzzyRuleConsequent *hasil_naikCepat = new FuzzyRuleConsequent();
  hasil_naikCepat->addOutput(naikCepat);

  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, asam_netral, hasil_naikCepat);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 3
  FuzzyRuleAntecedent *asam_negatif = new FuzzyRuleAntecedent();
  asam_negatif->joinWithAND(asam, negatif);

  FuzzyRuleConsequent *hasil_naikCepat = new FuzzyRuleConsequent();
  hasil_naikCepat->addOutput(naikCepat);

  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, asam_negatif, hasil_naikCepat);
  fuzzy->addFuzzyRule(fuzzyRule3);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 4
  FuzzyRuleAntecedent *netral_positif = new FuzzyRuleAntecedent();
  netral_positif->joinWithAND(netral, positif);

  FuzzyRuleConsequent *hasil_naikLambat = new FuzzyRuleConsequent();
  hasil_naikLambat->addOutput(naikLambat);

  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, netral_positif, hasil_naikCepat);
  fuzzy->addFuzzyRule(fuzzyRule4);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 5
  FuzzyRuleAntecedent *netral_netral = new FuzzyRuleAntecedent();
  netral_netral->joinWithAND(netral, netral);

  FuzzyRuleConsequent *hasil_berhenti = new FuzzyRuleConsequent();
  hasil_berhenti->addOutput(berhenti);

  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, netral_netral, hasil_berhenti);
  fuzzy->addFuzzyRule(fuzzyRule5);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 6
  FuzzyRuleAntecedent *netral_negatif = new FuzzyRuleAntecedent();
  netral_negatif->joinWithAND(netral, negatif);

  FuzzyRuleConsequent *hasil_turunLambat = new FuzzyRuleConsequent();
  hasil_turunLambat->addOutput(turunLambat);

  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, netral_negatif, hasil_turunLambat);
  fuzzy->addFuzzyRule(fuzzyRule6);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 7
  FuzzyRuleAntecedent *basa_positif = new FuzzyRuleAntecedent();
  basa_positif->joinWithAND(basa, positif);

  FuzzyRuleConsequent *hasil_turunCepat = new FuzzyRuleConsequent();
  hasil_turunCepat->addOutput(turunCepat);

  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, basa_positif, hasil_turunCepat);
  fuzzy->addFuzzyRule(fuzzyRule7);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 8
  FuzzyRuleAntecedent *basa_netral = new FuzzyRuleAntecedent();
  basa_netral->joinWithAND(basa, netral);

  FuzzyRuleConsequent *hasil_turunCepat = new FuzzyRuleConsequent();
  hasil_turunCepat->addOutput(turunCepat);

  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, basa_netral, hasil_turunCepat);
  fuzzy->addFuzzyRule(fuzzyRule8);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *basa_negatif = new FuzzyRuleAntecedent();
  basa_negatif->joinWithAND(basa, negatif);

  FuzzyRuleConsequent *hasil_turunCepat = new FuzzyRuleConsequent();
  hasil_turunCepat->addOutput(turunCepat);

  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, basa_negatif, hasil_turunCepat);
  fuzzy->addFuzzyRule(fuzzyRule9);

}



void loop()
{
  int in_analog1 = analogRead(pin_pot1);
  int in_analog2 = analogRead(pin_pot2);

//  int in_analog1 = random(0, 1023);
//  int in_analog2 = random(0, 1023);
  
  //--------------------------------------

  fuzzy->setInput(1, in_analog1);
  fuzzy->setInput(2, in_analog2);
  fuzzy->fuzzify();


  int out_led = fuzzy->defuzzify(1);
  analogWrite(pin_led , out_led);

  //--------------------------------------
  
  Serial.print("pot1    ");
  Serial.print(in_analog1);  Serial.println("  bit");
  Serial.print("pot2    ");
  Serial.print(in_analog2);  Serial.println("  bit");

  //---------------------

  Serial.print(in_analog1);   Serial.print(" ");
  Serial.println(in_analog2);
  Serial.println(" ");

  Serial.println("Result: ");
  Serial.print("       led: ");
  Serial.println(out_led);
  Serial.println("");
  Serial.println("");
}
