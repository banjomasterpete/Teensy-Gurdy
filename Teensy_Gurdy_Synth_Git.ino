#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>
#include "Adafruit_MPR121.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform8;      //xy=65,443
AudioSynthWaveform       waveform5;      //xy=66,312
AudioSynthWaveform       waveform7;      //xy=66,399
AudioSynthWaveform       waveform4;      //xy=67,253
AudioSynthWaveform       waveform6;      //xy=67,356
AudioSynthWaveform       waveform2;      //xy=68,171
AudioSynthWaveform       waveform3;      //xy=68,212
AudioSynthWaveform       waveform9;      //xy=67,531
AudioSynthWaveform       waveform1;      //xy=69,130
AudioSynthWaveform       waveform11;     //xy=69,619
AudioSynthWaveform       waveform12;     //xy=69,661
AudioSynthWaveform       waveform10;     //xy=70,575
AudioEffectEnvelope      envelope1;      //xy=216,130
AudioEffectEnvelope      envelope4;      //xy=216,256
AudioEffectEnvelope      envelope2;      //xy=217,173
AudioEffectEnvelope      envelope3;      //xy=217,213
AudioEffectEnvelope      envelope5;      //xy=218,311
AudioEffectEnvelope      envelope6;      //xy=218,355
AudioEffectEnvelope      envelope7;      //xy=218,400
AudioEffectEnvelope      envelope8;      //xy=218,443
AudioEffectEnvelope      envelope9;      //xy=220,531
AudioEffectEnvelope      envelope10;     //xy=221,575
AudioEffectEnvelope      envelope11;     //xy=222,621
AudioEffectEnvelope      envelope12;     //xy=222,662
AudioMixer4              mixer1;         //xy=379,196
AudioMixer4              mixer2;         //xy=387,371
AudioMixer4              mixer3;         //xy=391,598
AudioMixer4              mixer5;         //xy=535,767
AudioMixer4              mixer4;         //xy=549,373
AudioFilterStateVariable filter1;        //xy=585,442
AudioOutputI2S           i2s1;           //xy=673,767
AudioAmplifier           amp1;           //xy=683,373
AudioConnection          patchCord1(waveform8, envelope8);
AudioConnection          patchCord2(waveform5, envelope5);
AudioConnection          patchCord3(waveform7, envelope7);
AudioConnection          patchCord4(waveform4, envelope4);
AudioConnection          patchCord5(waveform6, envelope6);
AudioConnection          patchCord6(waveform2, envelope2);
AudioConnection          patchCord7(waveform3, envelope3);
AudioConnection          patchCord8(waveform9, envelope9);
AudioConnection          patchCord9(waveform1, envelope1);
AudioConnection          patchCord10(waveform11, envelope11);
AudioConnection          patchCord11(waveform12, envelope12);
AudioConnection          patchCord12(waveform10, envelope10);
AudioConnection          patchCord13(envelope1, 0, mixer1, 0);
AudioConnection          patchCord14(envelope4, 0, mixer1, 3);
AudioConnection          patchCord15(envelope2, 0, mixer1, 1);
AudioConnection          patchCord16(envelope3, 0, mixer1, 2);
AudioConnection          patchCord17(envelope5, 0, mixer2, 0);
AudioConnection          patchCord18(envelope6, 0, mixer2, 1);
AudioConnection          patchCord19(envelope7, 0, mixer2, 2);
AudioConnection          patchCord20(envelope8, 0, mixer2, 3);
AudioConnection          patchCord21(envelope9, 0, mixer3, 0);
AudioConnection          patchCord22(envelope10, 0, mixer3, 1);
AudioConnection          patchCord23(envelope11, 0, mixer3, 2);
AudioConnection          patchCord24(envelope12, 0, mixer3, 3);
AudioConnection          patchCord26(mixer1, 0, mixer4, 0);
AudioConnection          patchCord27(mixer2, 0, mixer4, 1);
AudioConnection          patchCord28(mixer3, 0, mixer4, 2);
AudioConnection          patchCord29(mixer5, 0, i2s1, 0);
AudioConnection          patchCord30(mixer5, 0, i2s1, 1);
AudioConnection          patchCord31(mixer4, amp1);
AudioConnection          patchCord32(filter1, 0, mixer5, 0);
AudioConnection          patchCord34(amp1, 0, filter1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=237,722
// GUItool: end automatically generated code
#define AmpSwitch 2
#define WaveSwitch 3
#define encoder0PinA 4
#define encoder0PinB 5
#define MS0 A3 //These pins are connected to S0-S3 and Z on the 4067 multiplexer
#define MS1 A6
#define MS2 8
#define MS3 A7
#define MZ  A2
#define MnumControls 16

#define MUXpitch1  0
#define MUXpitch2  1
#define MUXpitch3  2
#define MUXpitch4  3
#define MUXpitch5  4
#define MUXpitch6  5
#define MUXpitch7  6
#define MUXpitch8  7
#define MUXpitch9  8
#define MUXpitch10 9
#define MUXpitch11 10
#define MUXpitch12 11
#define MUXfilres  12
#define MUXmotor   13
#define MUXvolume  14
#define MUXenv     15

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();


uint16_t lasttouched = 0;
uint16_t currtouched = 0;
float ampstart = 0.75;
int pitchstart = 440;
int envatk = 50;
int envdec = 1;
int envsus = 1;
int envrel = 250;
int cutoff;
float amp;
int WaveState = 0;
int lastWaveSwitch;
int lastAmpSwitch;

volatile long encoder0Pos=0;
long newposition;
long oldposition = 0;
unsigned long newtime;
unsigned long oldtime = 0;
long vel;

int droneflag6 = 0;
int droneflag7 = 0;
int droneflag8 = 0;

void setup() {
  AudioMemory (20);
  
  pinMode(MS0, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(WaveSwitch, INPUT_PULLUP);
  pinMode(AmpSwitch, INPUT_PULLUP);
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  attachInterrupt(4, doEncoder, RISING);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(ampstart);
  waveform1.frequency(pitchstart);
  
  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(ampstart);
  waveform2.frequency(pitchstart);

  waveform3.begin(WAVEFORM_SAWTOOTH);
  waveform3.amplitude(ampstart);
  waveform3.frequency(pitchstart);

  waveform4.begin(WAVEFORM_SAWTOOTH);
  waveform4.amplitude(ampstart);
  waveform4.frequency(pitchstart);

  waveform5.begin(WAVEFORM_SAWTOOTH);
  waveform5.amplitude(ampstart);
  waveform5.frequency(pitchstart);
  
  waveform6.begin(WAVEFORM_SAWTOOTH);
  waveform6.amplitude(ampstart);
  waveform6.frequency(pitchstart);

  waveform7.begin(WAVEFORM_SAWTOOTH);
  waveform7.amplitude(ampstart);
  waveform7.frequency(pitchstart);

  waveform8.begin(WAVEFORM_SAWTOOTH);
  waveform8.amplitude(ampstart);
  waveform8.frequency(pitchstart);

  waveform9.begin(WAVEFORM_SAWTOOTH);
  waveform9.amplitude(ampstart);
  waveform9.frequency(pitchstart);
  
  waveform10.begin(WAVEFORM_SAWTOOTH);
  waveform10.amplitude(ampstart);
  waveform10.frequency(pitchstart);

  waveform11.begin(WAVEFORM_SAWTOOTH);
  waveform11.amplitude(ampstart);
  waveform11.frequency(pitchstart);

  waveform12.begin(WAVEFORM_SAWTOOTH);
  waveform12.amplitude(ampstart);
  waveform12.frequency(pitchstart);

  mixer1.gain (0, 1.0);
  mixer1.gain (1, 1.0);
  mixer1.gain (2, 1.0);
  mixer1.gain (3, 1.0);
  
  mixer2.gain (0, 1.0);
  mixer2.gain (1, 1.0);
  mixer2.gain (2, 1.0);
  mixer2.gain (3, 1.0);

  mixer3.gain (0, 1.0);
  mixer3.gain (1, 1.0);
  mixer3.gain (2, 1.0);
  mixer3.gain (3, 1.0);

  mixer4.gain (0, 1.0);
  mixer4.gain (1, 1.0);
  mixer4.gain (2, 1.0);
  mixer4.gain (3, 0.0);

  mixer5.gain (0, 1.0);
  mixer5.gain (1, 0.0);
  mixer5.gain (2, 0.0);
  mixer5.gain (3, 0.0);

  envelope1.attack(envatk);
  envelope1.decay (envdec);
  envelope1.sustain (envsus);
  envelope1.release (envrel);
  
  envelope2.attack(envatk);
  envelope2.decay (envdec);
  envelope2.sustain (envsus);
  envelope2.release (envrel);
  
  envelope3.attack(envatk);
  envelope3.decay (envdec);
  envelope3.sustain (envsus);
  envelope3.release (envrel);
  
  envelope4.attack(envatk);
  envelope4.decay (envdec);
  envelope4.sustain (envsus);
  envelope4.release (envrel);

  envelope5.attack(envatk);
  envelope5.decay (envdec);
  envelope5.sustain (envsus);
  envelope5.release (envrel);
  
  envelope6.attack(envatk);
  envelope6.decay (envdec);
  envelope6.sustain (envsus);
  envelope6.release (envrel);
  
  envelope7.attack(envatk);
  envelope7.decay (envdec);
  envelope7.sustain (envsus);
  envelope7.release (envrel);
  
  envelope8.attack(envatk);
  envelope8.decay (envdec);
  envelope8.sustain (envsus);
  envelope8.release (envrel);

  envelope9.attack(envatk);
  envelope9.decay (envdec);
  envelope9.sustain (envsus);
  envelope9.release (envrel);
  
  envelope10.attack(envatk);
  envelope10.decay (envdec);
  envelope10.sustain (envsus);
  envelope10.release (envrel);
  
  envelope11.attack(envatk);
  envelope11.decay (envdec);
  envelope11.sustain (envsus);
  envelope11.release (envrel);
  
  envelope12.attack(envatk);
  envelope12.decay (envdec);
  envelope12.sustain (envsus);
  envelope12.release (envrel);

  amp1.gain(0.5);

  filter1.frequency(20);
  filter1.resonance(0.7);

  cap.begin(0x5A);
  Serial.begin(9600);
}

void loop() { 
  checkGates ();
  checkMux ();
  checkSwitch ();  
if ((millis() - oldtime) > 100) {
  newposition = encoder0Pos;
  newtime = millis();
  vel = (abs(newposition-oldposition)) * 1000 /(newtime-oldtime);
  cutoff = map (vel, 0, 3200, 0, 12000);
  filter1.frequency (cutoff);
  oldposition = newposition;
  oldtime = newtime;
  }
}

void checkGates () { //This is all from the code example on Adafruit's MPR121 library
  currtouched = cap.touched();

  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if (i==0) {
        envelope1.noteOn(); //momentary envelope behavior
      }
      if (i==1) {
        envelope2.noteOn();
      }
      if (i==2) {
        envelope3.noteOn();
      }
      if (i==3) {
        envelope4.noteOn();
      }
      if (i==4) {
        envelope5.noteOn();
      }
      if (i==5) {
        if (droneflag6 == 0) {
          envelope6.noteOn(); //toggling envelope behavior for drones
          droneflag6 = 1;
        }
        else {
          envelope6.noteOff();
          droneflag6 = 0;
        }
      }
      if (i==6) {
        if (droneflag7 == 0) {
          envelope7.noteOn();
          droneflag7 = 1;
        }
        else {
          envelope7.noteOff();
          droneflag7 = 0;
        }
      }
      if (i==7) {
        if (droneflag8 == 0) {
          envelope8.noteOn();
          droneflag8 = 1;
        }
        else {
          envelope8.noteOff();
          droneflag8 = 0;
        }
      }
      if (i==8) {
        envelope9.noteOn();
      }
      if (i==9) {
        envelope10.noteOn();
      }
      if (i==10) {
        envelope11.noteOn();
      }
      if (i==11) {
        envelope12.noteOn();
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      if (i==0) {
        envelope1.noteOff();
      }
      if (i==1) {
        envelope2.noteOff();
      }
      if (i==2) {
        envelope3.noteOff();
      }
      if (i==3) {
        envelope4.noteOff();
      }
      if (i==4) {
        envelope5.noteOff();
      }
      if (i==8) {
        envelope9.noteOff();
      }
      if (i==9) {
        envelope10.noteOff();
      }
      if (i==10) {
        envelope11.noteOff();
      }
      if (i==11) {
        envelope12.noteOff();
      }
    }
  }

  lasttouched = currtouched;
}

void checkMux() { //This code is based on the Notes & Volts Teensy synth project. Go check out our old pal Dave!
  static byte muxInput = 0;
  static int muxValues[MnumControls] = {};
  unsigned long currentMicros = micros();

  if (currentMicros >= 1000) {

    int muxRead = analogRead(MZ);

      muxValues[muxInput] = muxRead;
      switch (muxInput) {
        case MUXpitch1:
          muxRead = map (muxRead, 0, 1023, 20, 200); //This frequency range of ~E0-G3 bounds the bass strings
          waveform1.frequency(muxRead);
          break;
        case MUXpitch2:
          muxRead = map (muxRead, 0, 1023, 20, 200);
          waveform2.frequency(muxRead);
          break;
        case MUXpitch3:
          muxRead = map (muxRead, 0, 1023, 20, 200);
          waveform3.frequency(muxRead);
          break;
        case MUXpitch4:
          muxRead = map (muxRead, 0, 1023, 150, 1400); //This frequency range of ~D3-F6 bounds the treble strings
          waveform4.frequency(muxRead);
          break;
        case MUXpitch5:
          muxRead = map (muxRead, 0, 1023, 150, 1400);
          waveform5.frequency(muxRead);
          break;
        case MUXpitch6: // drone 1
          muxRead = map (muxRead, 0, 1023, 20, 200);
          waveform6.frequency(muxRead);
          break;
        case MUXpitch7: // drone 2
          muxRead = map (muxRead, 0, 1023, 150, 1400);
          waveform7.frequency(muxRead);
          break;
        case MUXpitch8: // drone 3
          muxRead = map (muxRead, 0, 1023, 150, 1400);
          waveform8.frequency(muxRead);
          break;
        case MUXpitch9:
          muxRead = map (muxRead, 0, 1023, 150, 1400);
          waveform9.frequency(muxRead);
          break;
        case MUXpitch10:
          muxRead = map (muxRead, 0, 1023, 150, 1400);
          waveform10.frequency(muxRead);
          break;
        case MUXpitch11:
          muxRead = map (muxRead, 0, 1023, 150, 1400);
          waveform11.frequency(muxRead);
          break;
        case MUXpitch12:
          muxRead = map (muxRead, 0, 1023, 150, 1400);
          waveform12.frequency(muxRead);
          break;
        case MUXfilres:
          muxRead = map (muxRead, 0, 1023, 0.7, 5.0);
          filter1.resonance(muxRead); 
          break;
        case MUXvolume:
          amp = float(muxRead);
          amp = map (amp, 0.0, 1023.0, 0.0, 1.0);
          amp1.gain(amp);
          break;
        case MUXenv:
          muxRead = map (muxRead, 0, 1023, 50, 1000);
          envelope1.attack(muxRead);
          envelope1.release(muxRead);
          envelope2.attack(muxRead);
          envelope2.release(muxRead);
          envelope3.attack(muxRead);
          envelope3.release(muxRead);
          envelope4.attack(muxRead);
          envelope4.release(muxRead);
          envelope5.attack(muxRead);
          envelope5.release(muxRead);
          envelope6.attack(muxRead);
          envelope6.release(muxRead);
          envelope7.attack(muxRead);
          envelope7.release(muxRead);
          envelope8.attack(muxRead);
          envelope8.release(muxRead);
          envelope9.attack(muxRead);
          envelope9.release(muxRead);
          envelope10.attack(muxRead);
          envelope10.release(muxRead);
          envelope11.attack(muxRead);
          envelope11.release(muxRead);
          envelope12.attack(muxRead);
          envelope12.release(muxRead);
      }
    }
    muxInput++;
    if (muxInput >= MnumControls) muxInput = 0;
    digitalWrite(MS0, muxInput & B0001);
    digitalWrite(MS1, muxInput & B0010);
    digitalWrite(MS2, muxInput & B0100);
    digitalWrite(MS3, muxInput & B1000);
  }


void checkSwitch () {
  WaveState = digitalRead (WaveSwitch); //Checking if the wavestate switch has changed position, if so, initialize all waveforms with new shape
    if (WaveState != lastWaveSwitch) {
      if (WaveState == HIGH) {
        waveform1.begin(WAVEFORM_SQUARE);
        waveform2.begin(WAVEFORM_SQUARE);
        waveform3.begin(WAVEFORM_SQUARE);
        waveform4.begin(WAVEFORM_SQUARE);
        waveform5.begin(WAVEFORM_SQUARE);
        waveform6.begin(WAVEFORM_SQUARE);
        waveform7.begin(WAVEFORM_SQUARE);
        waveform8.begin(WAVEFORM_SQUARE);
        waveform9.begin(WAVEFORM_SQUARE);
        waveform10.begin(WAVEFORM_SQUARE);
        waveform11.begin(WAVEFORM_SQUARE);
        waveform12.begin(WAVEFORM_SQUARE);
     }
      else if (WaveState == LOW) {
        waveform1.begin(WAVEFORM_SAWTOOTH);
        waveform2.begin(WAVEFORM_SAWTOOTH);
        waveform3.begin(WAVEFORM_SAWTOOTH);
        waveform4.begin(WAVEFORM_SAWTOOTH);
        waveform5.begin(WAVEFORM_SAWTOOTH);
        waveform6.begin(WAVEFORM_SAWTOOTH);
        waveform7.begin(WAVEFORM_SAWTOOTH);
        waveform8.begin(WAVEFORM_SAWTOOTH);
        waveform9.begin(WAVEFORM_SAWTOOTH);
        waveform10.begin(WAVEFORM_SAWTOOTH);
        waveform11.begin(WAVEFORM_SAWTOOTH);
        waveform12.begin(WAVEFORM_SAWTOOTH);
      }
      lastWaveSwitch = WaveState;
    }
    
    if (digitalRead (AmpSwitch)) {
      filter1.frequency (5000); //If ampswitch is pulled HIGH, set the filter cutoff open for tuning
    }
}

void doEncoder() 
{
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }
}
