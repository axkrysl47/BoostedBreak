/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  BoostedCANMsgInfo.h
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#pragma once
#include "BoostedCANMsg.h"

#ifndef __BOOSTEDCANMSGINFOH__
#define __BOOSTEDCANMSGINFOH__

#define NUM_BOOSTED_CAN_MSG (39)

#define LENGTH_UNKNOWN (0)

#define INTERVAL_UNKNOWN    (0)
#define INTERVAL_INIT       (1)
#define INTERVAL_EVENT      (2)
#define INTERVAL_RESPONSE   (3)
#define INTERVAL_FASTEST    (20) // Special interval case values must be below fastest interval.

class BoostedCANMsgInfo
{
public:
    uint16_t Index;
    uint8_t Length;
    uint16_t Interval;
    std::string Sender;
    std::string Description;
    std::string Interpretation;

    BoostedCANMsgInfo()
    {
        Index = NUM_BOOSTED_CAN_MSG;
        Length = LENGTH_UNKNOWN;
        Interval = 0;
        Sender = "N/A";
        Description = "Unknown";
        Interpretation = "n/a";
    }

    BoostedCANMsgInfo(uint16_t indx, uint8_t lenh, uint16_t freq, std::string desc, std::string intp)
    {
        Index = indx;
        Length = lenh;
        Interval = freq;
        Sender = "N/A";
        Description = desc;
        Interpretation = intp;
    }

    BoostedCANMsgInfo(BoostedCANMsg message)
    {
        uint32_t id = message.MessageID;
        std::string buffer = message.MessageBufferAsString();
        std::string section = "";
        uint32_t num = 0;
        char charSection[8];

        Interval = INTERVAL_UNKNOWN;

        switch (id)
        {
        case (0x00000):
            Index = 0;
            Length = 4;
            Interval = INTERVAL_INIT;
            Sender = "N/A";
            Description = "PCAN-Basic Notification";
            Interpretation = "";

            section = buffer.substr(6, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 4)
            {
                Interpretation.append("        ");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x02402):
            Index = 1;
            Length = 8;
            Sender = "ESC";
            Description = "Version / Serial (to SRB)";
            Interpretation = "v";

            section = buffer.substr(12, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(14, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(0, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num));

            Interpretation.append(" / ");

            Interpretation.append("BoostedBoard");

            section = buffer.substr(10, 2);
            Interpretation.append(section);

            section = buffer.substr(8, 2);
            Interpretation.append(section);

            section = buffer.substr(6, 2);
            Interpretation.append(section);

            section = buffer.substr(4, 2);
            Interpretation.append(section);

            break;
        case (0x02411):
            Index = 2;
            Length = 8;
            Sender = "SRB";
            Description = "Debug Message (Continued)";
            Interpretation = "";

            Interpretation += (char)message.MessageBuffer[0];
            Interpretation += (char)message.MessageBuffer[1];
            Interpretation += (char)message.MessageBuffer[2];
            Interpretation += (char)message.MessageBuffer[3];
            Interpretation += (char)message.MessageBuffer[4];
            Interpretation += (char)message.MessageBuffer[5];
            Interpretation += (char)message.MessageBuffer[6];
            Interpretation += (char)message.MessageBuffer[7];

            break;
        case (0x05415):
            Index = 3;
            Length = 8;
            Sender = "XRB";
            Description = "Version Registration";
            Interpretation = "v";

            section = buffer.substr(4, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(6, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(8, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num));

            Interpretation.append(" / ");

            section = buffer.substr(12, 4);
            if (section == "A20F")
            {
                Interpretation.append("XRB");
            }
            else if (section == "C409")
            {
                Interpretation.append("SRB");
            }
            else
            {
                Interpretation.append("Unknown");
            }

            break;
        case (0x12402):
            Index = 4;
            Length = 1;
            Sender = "SRB";
            Description = "Release";
            Interpretation = "";

            section = buffer.substr(0, 2);

            if (buffer == "02")
            {
                Interpretation.append("Public");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x12411):
            Index = 5;
            Length = 8;
            Sender = "SRB";
            Description = "Debug Message (End)";
            Interpretation = "";

            Interpretation += (char)message.MessageBuffer[0];
            Interpretation += (char)message.MessageBuffer[1];
            Interpretation += (char)message.MessageBuffer[2];
            Interpretation += (char)message.MessageBuffer[3];
            Interpretation += (char)message.MessageBuffer[4];
            Interpretation += (char)message.MessageBuffer[5];
            Interpretation += (char)message.MessageBuffer[6];
            Interpretation += (char)message.MessageBuffer[7];

            break;
        case (0x13417):
            // Polling
            Index = 6;
            Length = 1;
            Interval = 20;
            Sender = "XRB";
            Description = "Debug Code (End)";
            Interpretation = "";

            section = buffer.substr(0, 2);

            if (section == "00")
            {
                Interpretation.append("Sent from XRB");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x15415):
            Index = 7;
            Length = 3;
            Sender = "XRB";
            Description = "Release";
            Interpretation = "";

            section = buffer.substr(4, 2);

            if (section == "02")
            {
                Interpretation.append("Public");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x22402):
            Index = 8;
            Length = 8;
            Sender = "SRB";
            Description = "Unknown (Incrementer?)";
            Interpretation = "";

            section = buffer.substr(0, 2);
            num = ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x00000001);

            section = buffer.substr(2, 2);
            num += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x00000100);

            section = buffer.substr(4, 2);
            num += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x00010000);

            section = buffer.substr(6, 2);
            num += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x01000000);

            Interpretation.append(std::to_string(num));

            Interpretation.append(" / ");

            section = buffer.substr(8, 2);
            if (section == "03")
            {
                Interpretation.append("SRB");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x22411):
            Index = 9;
            Length = 8;
            Sender = "SRB";
            Description = "Debug Message (Start)";
            Interpretation = "";

            Interpretation += (char)message.MessageBuffer[0];
            Interpretation += (char)message.MessageBuffer[1];
            Interpretation += (char)message.MessageBuffer[2];
            Interpretation += (char)message.MessageBuffer[3];
            Interpretation += (char)message.MessageBuffer[4];
            Interpretation += (char)message.MessageBuffer[5];
            Interpretation += (char)message.MessageBuffer[6];
            Interpretation += (char)message.MessageBuffer[7];

            break;
        case (0x23417):
            // Polling
            Index = 10;
            Length = 8;
            Interval = 20;
            Sender = "XRB";
            Description = "Debug Code (Start)";
            Interpretation = "Decimal: ";
            int64_t sum;

            section = buffer.substr(0, 2);
            sum = ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0000000000000001);

            section = buffer.substr(2, 2);
            sum += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0000000000000100);

            section = buffer.substr(4, 2);
            sum += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0000000000010000);

            section = buffer.substr(6, 2);
            sum += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0000000001000000);

            section = buffer.substr(8, 2);
            sum += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0000000100000000);

            section = buffer.substr(10, 2);
            sum += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0000010000000000);

            section = buffer.substr(12, 2);
            sum += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0001000000000000);

            section = buffer.substr(14, 2);
            sum += ((uint64_t)(std::stoul(section, nullptr, 16)) * 0x0100000000000000);

            Interpretation.append(std::to_string(sum));

            break;
        case (0x25415):
            Index = 11;
            Length = 8;
            Sender = "XRB";
            Description = "Serial Registration";
            Interpretation = "BoostedBattery";

            section = buffer.substr(4, 2);
            num = (std::stoul(section, nullptr, 16) * 0x00000001);

            section = buffer.substr(6, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00000100);

            section = buffer.substr(8, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00010000);

            section = buffer.substr(10, 2);
            num += (std::stoul(section, nullptr, 16) * 0x01000000);

            Interpretation.append(std::to_string(num));

            break;
        case (0x32411):
            Index = 12;
            Length = 8;
            Sender = "SRB";
            Description = "Debug Message (Address)";
            Interpretation = "n/a";
            
            Interpretation += (char)message.MessageBuffer[0];
            Interpretation += (char)message.MessageBuffer[1];
            Interpretation += (char)message.MessageBuffer[2];
            Interpretation += (char)message.MessageBuffer[3];
            Interpretation += (char)message.MessageBuffer[4];
            Interpretation += (char)message.MessageBuffer[5];
            Interpretation += (char)message.MessageBuffer[6];
            Interpretation += (char)message.MessageBuffer[7];

            break;
        case (0x33417):
            Index = 13;
            Length = LENGTH_UNKNOWN;
            Sender = "XRB";
            Description = "Registration State (to ESC)";
            Interpretation = "";

            section = buffer.substr(0, 4);

            if (section == "010A")
            {
                Interpretation.append("Standby");
            }
            else
            {
                section = buffer.substr(0, 14);

                if (section == "007D0064006400")
                {
                    Interpretation.append("ESC Registration Request");
                }
                else
                {
                    Interpretation.append("Unknown!");
                }
            }

            break;
        case (0x33440):
            Index = 14;
            Length = 8;
            Sender = "BTY";
            Description = "Version";
            Interpretation = "v";

            section = buffer.substr(0, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(2, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(4, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num));

            break;
        case (0x33441):
            Index = 15;
            Length = 8;
            Sender = "BTY";
            Description = "Serial";
            Interpretation = "BoostedBattery";

            section = buffer.substr(0, 2);
            num = (std::stoul(section, nullptr, 16) * 0x00000001);

            section = buffer.substr(2, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00000100);

            section = buffer.substr(4, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00010000);

            section = buffer.substr(6, 2);
            num += (std::stoul(section, nullptr, 16) * 0x01000000);

            Interpretation.append(std::to_string(num));

            break;
        case (0x33442):
            // Polling
            Index = 16;
            Length = 8;
            Interval = 250;
            Sender = "BTY";
            Description = "Ping";
            Interpretation = "";

            if (buffer == "0000A20F00000000")
            {
                Interpretation.append("Sent by XRB");
            }
            else if (buffer == "0000C40900000000")
            {
                Interpretation.append("Sent by SRB");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x33443):
            Index = 17;
            Length = 8;
            Sender = "BTY";
            Description = "Identifier";
            Interpretation = "";

            if (buffer == "D20FCA080C000000")
            {
                Interpretation.append("SRB ID  ");
            }
            else if (buffer == "8110C4090D000000")
            {
                Interpretation.append("XRB ID  ");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x33444):
            // Not Used
            Index = 18;
            Length = 8;
            Sender = "N/A";
            Description = "Not Used";
            Interpretation = "Unrecognized!";

            break;
        case (0x33445):
            // Polling
            Index = 19;
            Length = 8;
            Interval = 20;
            Sender = "BTY";
            Description = "Voltages";
            Interpretation = "Lo= ";

            section = buffer.substr(0, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(2, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            Interpretation.append(std::to_string(num));
            Interpretation.append("mV ");

            Interpretation.append("Hi= ");

            section = buffer.substr(4, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(6, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            Interpretation.append(std::to_string(num));
            Interpretation.append("mV ");

            Interpretation.append("Pk= ");

            section = buffer.substr(8, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(10, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            Interpretation.append(std::to_string(num));
            Interpretation.append("mV ");

            break;
        case (0x33446):
            // Polling
            Index = 20;
            Length = 8;
            Interval = 2000;
            Sender = "BTY";
            Description = "Unknown (Calibration?)";
            Interpretation = "";

            section = buffer.substr(0, 2);
            num = (std::stoul(section, nullptr, 16) * 0x00000001);

            section = buffer.substr(2, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00000100);

            section = buffer.substr(4, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00010000);

            section = buffer.substr(6, 2);
            num += (std::stoul(section, nullptr, 16) * 0x01000000);

            Interpretation.append(std::to_string(num));

            Interpretation.append(" / ");

            section = buffer.substr(8, 2);
            num = (std::stoul(section, nullptr, 16) * 0x00000001);

            section = buffer.substr(10, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00000100);

            section = buffer.substr(12, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00010000);

            section = buffer.substr(14, 2);
            num += (std::stoul(section, nullptr, 16) * 0x01000000);

            Interpretation.append(std::to_string(num));

            break;
        case (0x33447):
            // Polling
            Index = 21;
            Length = 8;
            Interval = 250;
            Sender = "BTY";
            Description = "Amperages";
            Interpretation = "";
            charSection[0] = 0;

            Interpretation = "10secAvg= ";

            section = buffer.substr(0, 2);
            num = (std::stoul(section, nullptr, 16) *  0x00000001);

            section = buffer.substr(2, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00000100);

            section = buffer.substr(4, 2);
            num += (std::stoul(section, nullptr, 16) *  0x00010000);

            section = buffer.substr(6, 2);
            num += (std::stoul(section, nullptr, 16) * 0x01000000);

            if (num & 0x80000000)
            {
                num *= -1;
            }
            else
            {
                charSection[0] = 1;
            }

            Interpretation.append(std::to_string(num));
            Interpretation.append("mA ");

            Interpretation.append("Current= ");

            section = buffer.substr(8, 2);
            num = (std::stoul(section, nullptr, 16) * 0x00000001);

            section = buffer.substr(10, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00000100);

            section = buffer.substr(12, 2);
            num += (std::stoul(section, nullptr, 16) * 0x00010000);

            section = buffer.substr(14, 2);
            num += (std::stoul(section, nullptr, 16) * 0x01000000);

            if (num & 0x80000000)
            {
                num *= -1;
            }
            else
            {
                charSection[0] = 1;
            }

            Interpretation.append(std::to_string(num));
            Interpretation.append("mA ");

            if (charSection[0] == 1)
            {
                Interpretation.append("(Charging)");
            }
            else
            {
                Interpretation.append("");
            }

            break;
        case (0x33448):
            // Polling
            Index = 22;
            Length = 8;
            Interval = 20;
            Sender = "BTY";
            Description = "Unknown (Counter?)";
            Interpretation = "";

            section = buffer.substr(0, 4);

            if (section == "0000")
            {
                Interpretation.append("Standby...");
            }
            else if (section == "B888")
            {
                Interpretation.append("Active (XRB)");
            }
            else if (section == "50C3")
            {
                Interpretation.append("Active (SRB)");
            }
            else if (section == "5C44")
            {
                Interpretation.append("Error (XRB)");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            Interpretation.append(" / ");

            section = buffer.substr(8, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(10, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            Interpretation.append(std::to_string(num));
            Interpretation.append(" counts");

            break;
        case (0x33449):
            // Polling
            Index = 23;
            Length = 8;
            Interval = 250;
            Sender = "BTY";
            Description = "State of Charge";
            Interpretation = "";

            section = buffer.substr(8, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num));
            Interpretation.append("%");

            Interpretation.append(" = ");

            section = buffer.substr(0, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(2, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            Interpretation.append(std::to_string(num));
            
            Interpretation.append("/");

            section = buffer.substr(4, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(6, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            Interpretation.append(std::to_string(num));
            Interpretation.append(" / ");

            section = buffer.substr(10, 6);
            if (section == "000500")
            {
                Interpretation.append("Normal");
            }
            else if (section == "000300")
            {
                Interpretation.append("Charged Previously");
            }
            else if (section == "000600")
            {
                Interpretation.append("Battery Error");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x3344A):
            // Polling
            Index = 24;
            Length = 8;
            Interval = 100;
            Sender = "BTY";
            Description = "State / Timer / Millis (LSB)";
            Interpretation = "";

            section = buffer.substr(0, 2);
            if (section == "00")
            {
                section = buffer.substr(8, 2);

                if (section == "00")
                {
                    Interpretation.append("Normal / ");
                }
                else if (section == "02")
                {
                    Interpretation.append("Shutting Down... (ESC Command) /");
                }
                else if (section == "03")
                {
                    Interpretation.append("Shutting Down... (Charger Disconnected) /");
                }
                else if (section == "05")
                {
                    Interpretation.append("Shutting Down... (Power Button Held) / ");
                }
                else
                {
                    Interpretation.append("Unknown! (State) / ");
                }
            }
            else if (section == "01")
            {
                Interpretation.append("Charger Connected / ");
            }
            else
            {
                Interpretation.append("Unknown! (Charger) / ");
            }

            section = buffer.substr(4, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(6, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            Interpretation.append(std::to_string(num));

            Interpretation.append("ms ");

            Interpretation.append("/ ");

            section = buffer.substr(12, 2);
            num = (std::stoul(section, nullptr, 16));
            sprintf_s(charSection, 8, "%03ld", (int) num);
            Interpretation.append(charSection);

            Interpretation.append("ms (LSB)");

            break;
        case (0x3344B):
            Index = 25;
            Length = 8;
            Sender = "N/A";
            Description = "Not Used";
            Interpretation = "Unrecognized!";

            break;
        case (0x3344C):
            Index = 26;
            Length = 8;
            Sender = "SRB";
            Description = "Button State";
            Interpretation = "";

            section = buffer.substr(0, 2);

            if (section == "01")
            {
                Interpretation.append("Pressed Once.");
            }
            else if (section == "02")
            {
                Interpretation.append("Pressed Twice.");
            }
            else if (section == "03")
            {
                Interpretation.append("Pressed Three Times.");
            }
            else if (section == "04")
            {
                Interpretation.append("Pressed Four Times.");
            }
            else if (section == "05")
            {
                Interpretation.append("Pressed Five Times.");
            }
            else if (section == "06")
            {
                Interpretation.append("Pressed!");
            }
            else if (section == "07")
            {
                Interpretation.append("Holding (<1.0s).");
            }
            else if (section == "08")
            {
                Interpretation.append("Holding (<2.0s).");
            }
            else if (section == "09")
            {
                Interpretation.append("Holding (2.0+s).");
            }
            else if (section == "0A")
            {
                Interpretation.append("Held    (<1.5s).");
            }
            else if (section == "0B")
            {
                Interpretation.append("Held    (<2.0s).");
            }
            else if (section == "0C")
            {
                Interpretation.append("Held    (2.0+s).");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            section = buffer.substr(2, 2);

            if (section == "00")
            {
                Interpretation.append("");
            }
            else if (section == "0E")
            {
                Interpretation.append(" / Pairing Mode Acknowledged");
            }
            else
            {
                Interpretation.append(" / Unknown!");
            }

            section = buffer.substr(4, 12);

            if (section != "000000000000")
            {
                Interpretation.append(" Unknown! (Suffix)");
            }

            break;
        case (0x3344D):
            Index = 27;
            Length = 8;
            Sender = "N/A";
            Description = "Not Used";
            Interpretation = "Unrecognized!";

            break;
        case (0x3344E):
            Index = 28;
            Length = 8;
            Sender = "BTY";
            Description = "Timestamp";
            Interpretation = "";

            Interpretation.append("2");

            // Year
            section = buffer.substr(12, 2);
            num = std::stoul(section, nullptr, 16) * 0x0001;

            section = buffer.substr(14, 2);
            num += std::stoul(section, nullptr, 16) * 0x0100;

            sprintf_s(charSection, 8, "%03ld", (int)num);
            Interpretation.append(charSection);

            Interpretation.append("/");

            // Month
            section = buffer.substr(10, 2);
            num = std::stoul(section, nullptr, 16);
            sprintf_s(charSection, 8, "%02ld", (int)num);
            Interpretation.append(charSection);

            Interpretation.append("/");

            // Date
            section = buffer.substr(6, 2);
            num = std::stoul(section, nullptr, 16);
            sprintf_s(charSection, 8, "%02ld", (int)num);
            Interpretation.append(charSection);

            Interpretation.append(" ");

            // Day
            section = buffer.substr(8, 2);
            if (section == "00")
            {
                Interpretation.append("Sunday");
            }
            else if (section == "01")
            {
                Interpretation.append("Monday");
            }
            else if (section == "02")
            {
                Interpretation.append("Tuesday");
            }
            else if (section == "03")
            {
                Interpretation.append("Wednesday");
            }
            else if (section == "04")
            {
                Interpretation.append("Thursday");
            }
            else if (section == "05")
            {
                Interpretation.append("Friday");
            }
            else if (section == "06")
            {
                Interpretation.append("Saturday");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            Interpretation.append(" ");

            // Hour
            section = buffer.substr(4, 2);
            num = std::stoul(section, nullptr, 16);
            sprintf_s(charSection, 8, "%02ld", (int)num);
            Interpretation.append(charSection);

            Interpretation.append(":");

            // Minute
            section = buffer.substr(2, 2);
            num = std::stoul(section, nullptr, 16);
            sprintf_s(charSection, 8, "%02ld", (int)num);
            Interpretation.append(charSection);

            Interpretation.append(":");

            // Second
            section = buffer.substr(0, 2);
            num = std::stoul(section, nullptr, 16);
            sprintf_s(charSection, 8, "%02ld", (int)num);
            Interpretation.append(charSection);

            break;
        case (0x3344F):
            Index = 29;
            Length = 8;
            Sender = "N/A";
            Description = "Not Used";
            Interpretation = "Unrecognized!";

            break;
        case (0x34316):
            Index = 30;
            Length = 3;
            Sender = "ESC";
            Description = "Registration State (to BTY)";
            Interpretation = "";

            section = buffer.substr(0, 6);

            if (section == "010C00")
            {
                Interpretation.append("BTY Registration Command");
            }
            else if (section == "020600")
            {
                Interpretation.append("ESC Registration Notification");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x34344):
            Index = 31;
            Length = 8;
            Sender = "ESC";
            Description = "Version / Serial";
            Interpretation = "v";

            section = buffer.substr(0, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(2, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num) + ".");

            section = buffer.substr(4, 2);
            num = std::stoul(section, nullptr, 16);
            Interpretation.append(std::to_string(num));

            Interpretation.append(" / ");

            Interpretation.append("BoostedBoard");

            section = buffer.substr(14, 2);
            Interpretation.append(section);

            section = buffer.substr(12, 2);
            Interpretation.append(section);

            section = buffer.substr(10, 2);
            Interpretation.append(section);

            section = buffer.substr(8, 2);
            Interpretation.append(section);

            section = buffer.substr(6, 2);
            if (section != "01")
            {
                Interpretation.append("Unknown! (Delimiter)");
            }

            break;
        case (0x3434B):
            // Polling
            Index = 32;
            Length = 8;
            Interval = 100;
            Sender = "ESC";
            Description = "Ping / Power";

            if (buffer == "0000000000000000")
            {
                Interpretation.append("Ping");
            }
            else if (buffer == "0200000000000000")
            {
                Interpretation.append("Power Off (via Remote Command)");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x3434C):
            Index = 33;
            Length = 8;
            Sender = "N/A";
            Description = "Not Used";
            Interpretation = "Unrecognized!";

            break;
        case (0x3434D):
            Index = 34;
            Length = 8;
            Interval = 1000;
            Sender = "SRB";
            Description = "Pairing Mode";
            Interpretation = "";

            section = buffer.substr(0, 2);
            num = (std::stoul(section, nullptr, 16) * 0x0001);

            section = buffer.substr(2, 2);
            num += (std::stoul(section, nullptr, 16) * 0x0100);

            if (num == 0x0000)
            {
                Interpretation.append("Exited Pairing.");
            }
            else if (num == 0x01D7)
            {
                Interpretation.append("Pairing Mode...");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x3B31A):
            Index = 35;
            Length = 3;
            Sender = "ESC";
            Description = "Mode";
            Interpretation = "";

            section = buffer.substr(2, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 0)
            {
                Interpretation.append("Mode 1 (Beginner)");
            }
            else if (num == 1)
            {
                Interpretation.append("Mode 2 (Eco)");
            }
            else if (num == 2)
            {
                Interpretation.append("Mode 3 (Expert)");
            }
            else if (num == 3)
            {
                Interpretation.append("Mode 4 (Pro)");
            }
            else if (num == 4)
            {
                Interpretation.append("Mode 5 (Hyper)");
            }
            else if (num == 5)
            {
                Interpretation.append("Charging... (SRB)");
            }
            else if (num == 6)
            {
                Interpretation.append("Shutting Down (SRB)");
            }
            else if (num == 21)
            {
                Interpretation.append("Pairing Mode...");
            }
            else if (num == 22)
            {
                Interpretation.append("Exited Pairing.");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            Interpretation.append(" / ");

            section = buffer.substr(4, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 0)
            {
                Interpretation.append("Up to Mode 1 Supported");
            }
            else if (num == 1)
            {
                Interpretation.append("Up to Mode 2 Supported");
            }
            else if (num == 2)
            {
                Interpretation.append("Up to Mode 3 Supported");
            }
            else if (num == 3)
            {
                Interpretation.append("Up to Mode 4 Supported");
            }
            else if (num == 4)
            {
                Interpretation.append("Up to Mode 5 Supported");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            break;
        case (0x3B41A):
            Index = 36;
            Length = 3;
            Sender = "XRB";
            Description = "Button State";
            Interpretation = "";

            section = buffer.substr(2, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 0x05)
            {
                Interpretation.append("Charging...");
            }
            else if (num == 0x06)
            {
                Interpretation.append("Shutting down...");
            }
            else if (num == 0x07)
            {
                Interpretation.append("Pressed!");
            }
            else if (num == 0x08)
            {
                Interpretation.append("Waiting...");
            }
            else if (num == 0x09)
            {
                Interpretation.append("Pressed Once.");
            }
            else if (num == 0x0A)
            {
                Interpretation.append("Pressed Twice.");
            }
            else if (num == 0x0B)
            {
                Interpretation.append("Pressed Three Times.");
            }
            else if (num == 0x0C)
            {
                Interpretation.append("Pressed Four Times.");
            }
            else if (num == 0x0D)
            {
                Interpretation.append("Pressed Five Times.");
            }
            else if (num == 0x0E)
            {
                Interpretation.append("Holding (<1.0s).");
            }
            else if (num == 0x0F)
            {
                Interpretation.append("Holding (<1.5s).");
            }
            else if (num == 0x10)
            {
                Interpretation.append("Holding (<2.0s).");
            }
            else if (num == 0x11)
            {
                Interpretation.append("Holding (<2.5s).");
            }
            else if (num == 0x12)
            {
                Interpretation.append("Held    (<1.5s).");
            }
            else if (num == 0x13)
            {
                Interpretation.append("Held    (<2.0s).");
            }
            else if (num == 0x14)
            {
                Interpretation.append("Pressed & Held (OFF)");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            /*Interpretation.append(" / Boosted ");

            section = buffer.substr(4, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 0)
            {
                Interpretation.append("Test(1)");
            }
            else if (num == 1)
            {
                Interpretation.append("Test(2)");
            }
            else if (num == 2)
            {
                Interpretation.append("Mini   ");
            }
            else if (num == 3)
            {
                Interpretation.append("Plus   ");
            }
            else if (num == 4)
            {
                Interpretation.append("Stealth");
            }*/

            break;
        case (0x33920):
            Index = 37;
            Length = 8;
            Sender = "ACC";
            Description = "Registration";
            Interpretation = "";

            section = buffer.substr(0, 2);

            if (section == "FE")
            {
                Interpretation.append("Registering ");
            }
            else
            {
                Interpretation.append("Unknown! ");
            }

            section = buffer.substr(10, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 0)
            {
                Interpretation.append("Headlights");
            }
            else if (num == 1)
            {
                Interpretation.append("Taillights");
            }
            else
            {
                Interpretation.append("Unknown!");
            }

            Interpretation.append(" / ");

            Interpretation.append("BoostedBeams");

            section = buffer.substr(14, 2);
            Interpretation.append(section);

            section = buffer.substr(12, 2);
            Interpretation.append(section);

            break;
        case (0x39320):
            Index = 38;
            Length = 8;
            Sender = "ESC";
            Description = "Command (to Accessory)";
            Interpretation = "";

            section = buffer.substr(0, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 0)
            {
                Interpretation.append("To Light 1");
                charSection[0] = 0;
            }
            else if (num == 1)
            {
                Interpretation.append("To Light 2");
                charSection[0] = 1;
            }
            else
            {
                Interpretation.append("Unknown!  ");
                charSection[0] = 2;
            }

            Interpretation.append(" - ");

            section = buffer.substr(4, 2);
            num = std::stoul(section, nullptr, 16);

            if (num == 34)
            {
                Interpretation.append("Light ON ");
            }
            else if (num == 35)
            {
                Interpretation.append("Light OFF");
            }
            else if (num == 98)
            {
                Interpretation.append("Blink ON ");
            }
            else if (num == 66)
            {
                Interpretation.append("Blink OFF");
            }
            else
            {
                Interpretation.append("Unknown! ");
            }

            // Assuming Headlight is Light 1
            if (charSection[0] == 0)
            {
                section = buffer.substr(6, 2);
                num = (std::stoul(section, nullptr, 16) * 100) / 255;
                sprintf_s(charSection, 8, "%02ld", (int)num);

                Interpretation.append("Brightness= ");
                Interpretation.append(charSection);
                Interpretation.append("%");
            }
            // Assuming Taillight is Light 2
            else if (num == 35)
            {
                section = buffer.substr(6, 2);
                if (section == "64")
                {
                    Interpretation.append("Brightness= MAX (Braking)");
                }
                else
                {
                    num = (std::stoul(section, nullptr, 16) * 100) / 51;
                    sprintf_s(charSection, 8, "%02ld", (int)num);

                    Interpretation.append("Brightness= ");
                    Interpretation.append(charSection);
                    Interpretation.append("%");
                }
            }
            else
            {
                //Interpretation.append("");
            }

            break; 
        default:
            Index = 39;
            Length = 8;
            Sender = "N/A";
            Description = "Not Recorded";
            Interpretation = "Not Recorded";

            break;
        }
    }
};

//uint32_t BoostedCANMsgInfo::BoostedCANMsgList = 
//{
//    0x00000, 0x02402, 0x02411, 0x05415, 0x12402, 0x12411, 0x13417, 0x15415,
//    0x24402, 0x22411, 0x23417, 0x25415, 0x32411, 0x33417, 0x33440, 0x33441,
//    0x33442, 0x33443, 0x33444, 0x33445, 0x33446, 0x33447, 0x33448, 0x33449,
//    0x3344A, 0x3344B, 0x3344C, 0x3344D, 0x3344E, 0x3344F, 0x34316, 0x34344,
//    0x3434B, 0x3434C, 0x3434D, 0x3B31A, 0x3B41A, 0x33920, 0x39320
//};

#endif //__BOOSTEDCANMSGINFOH__
