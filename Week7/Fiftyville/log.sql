-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Outcome:
-- gives the brief description of the crime scene

SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28;
-- gives the description of the interviewee
-- 1. Ruth - within 10 min theif left the parking lot
-- 2. Eugene - recognised him, and withdraw amount from atm in leggett street early that morning
-- 3. Raymond - will take earliest flight on 29 july, call duration less than a minute

-- 1. Ruth's Transcript output:

SELECT people.name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 ORDER BY hour, minute);
-- Outcome:
-- prints all the names of the people who left the bakery on the theft day within 10 mins of the theft
-- Names: Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce

-- 2. Eugene's Transcript output:

SELECT DISTINCT people.name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE atm_transactions.account_number IN (SELECT account_number FROM atm_transactions WHERE MONTH = 7 AND DAY = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street');
-- Outcome:
-- prints all the name of the people who withdraw any amount on 28 july in leggett street
-- Names: Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista

-- 3. Raymond's Transcript output:

-- Part 1
SELECT people.name FROM people WHERE phone_number IN (SELECT DISTINCT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60);
-- Outcome:
-- prints all the name of those who made a call on the theft day and the duration of the call was less than a min
-- Names: Kenny, Sofia, Benista, Taylor, Diana, Kelsey, Bruce, Carina

-- Part 2
SELECT people.name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT flights.id FROM airports JOIN flights ON airports.id = flights.destination_airport_id WHERE flights.month = 7 AND flights.day = 29 ORDER BY hour, minute LIMIT 1));
-- Outcome:
-- prints all the name of those who took a flight from the first plane on the next day of the theft
-- Names: Kenny, Sofia, Taylor, Luca, Kelsey, Edward, Bruce, Doris

-- Common Names in all four: Bruce AND Accomplice Name: Robin
-- PhoneNumber - (367) 555-5533 AND Accomplice PhoneNumber - (375) 555-8161
-- Bruce PassportNumber - 5773159633
