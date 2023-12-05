INSERT INTO Currencies (Name)
VALUES
  ('CZK'),
  ('USD'),
  ('EUR'),
  ('JPY'),
  ('GBP'),
  ('AUD'),
  ('CAD'),
  ('CHF'),
  ('SEK'),
  ('NOK'),
  ('DKK'),
  ('PLN'),
  ('HUF'),
  ('RUB');
--------------------------------------------
INSERT INTO Cryptocurrencies (Name)
VALUES
  ('BTC'),
  ('ETH'),
  ('XRP'),
  ('LTC'),
  ('BCH'),
  ('ADA'),
  ('DOT'),
  ('LINK'),
  ('XLM'),
  ('BNB'),
  ('DOGE'),
  ('USDT'),
  ('XMR'),
  ('UNI'),
  ('EOS'),
  ('TRX'),
  ('XTZ'),
  ('VET'),
  ('ATOM'),
  ('SOL');
----------------------------------------------------------------
INSERT INTO Users (Email, Password, Mobile_number, Investment_goals, Risk, Currency_ID)
VALUES
  ('adam.novak@email.com', 'AdamPwd_1a2b3c', '60212233', 1300000, 3, 1),
  ('linda.kriz@email.com', 'LindaPwd_4d5e6f', '17711233', 160000, 20, 2),
  ('tomas.prochazka@email.com', 'TomasPwd_7g8h9i', '71234567', 11000000, 4, 3),
  ('natalie.mareckova@email.com', 'NataliePwd_1j2k3l', '08765432', 140000, 1, 4),
  ('martin.svoboda@email.com', 'MartinPwd_4m5n6o', '75577577', 18000, 2, 5),
  ('tereza.dvorakova@email.com', 'TerezaPwd_7p8q9r', '60245678', 150000, 4, 6),
  ('jiri.horak@email.com', 'JiriPwd_1s2t3u', '70567901', 1200000, 3, 7),
  ('barbora.holcova@email.com', 'BarboraPwd_4v5w6x', '73322211', 170000, 5, 8),
  ('filip.kovac@email.com', 'FilipPwd_7y8z9a', '21789123', 1900000, 2, 9),
  ('lucie.mrazova@email.com', 'LuciePwd_1b2c3d', '60875432', 103000, 4, 10),
  ('patrik.juricek@email.com', 'PatrikPwd_4e5f6g', '31245678', 606000, 2, 11),
  ('emma.smith@email.com', 'EmmaPwd_7h8i9j', '71234678', 2742000, 3, 12),
  ('juan.perez@email.com', 'JuanPwd_1k2l3m', '1234578', 8027000, 4, 1),
  ('mario.rossi@email.com', 'MarioPwd_4n5o6p', '12356789', 5412000, 2, 2),
  ('yuki.tanaka@email.com', 'YukiPwd_7q8r9s', '8234578', 110000, 5, 3),
  ('sophie.dubois@email.com', 'SophiePwd_1t2u3v', '2356789', 140000, 7, 4),
  ('ali.khan@email.com', 'AliPwd_4w5x6y', '11234678', 16000, 40, 5),
  ('anita.mendoza@email.com', 'AnitaPwd_7z8a9b', '51235678', 13000, 20, 6),
  ('vikram.patel@email.com', 'VikramPwd_1c2d3e', '34568901', 70000, 5, 7),
  ('mariam.santos@email.com', 'MariamPwd_4f5g6h', '11234678', 15000, 3, 8);
----------------------------------------------------------------
INSERT INTO Admins (First_name, Last_name, State, City, Postal_code, User_ID)
VALUES
    ('Adam', 'Novak', 'Czech Republic', 'Ostrava', 12345, 1),
    ('Mario', 'Rossi', 'California', 'Los Angeles', 90001, 14),
    ('Anita', 'Mendoza', 'Cyprus', 'Limassol', 10001, 18),
    ('Yuki', 'Tanaka', 'Japan', 'Tokio', 77001, 15),
    ('Martin', 'Svoboda', 'Czech Republic', 'Cesky Tesin', 33101, 5);
----------------------------------------------------------------
INSERT INTO Portfolios (Title, Value, Volume, Wallet_address, User_ID)
VALUES
  ('Tech Portfolio', 50000.75, null, '0x6A09F56C7F3F1A7F0D8C4B6A1F1', 1),
  ('Finance Portfolio', 75000.25, 15.8, null , 2),
  ('Real Investment', 120000.50, 8.2, null, 3),
  ('Global Fund', 90000.80, 12.5, '0xC4D2C3B3E2F1A7D8C4B6A1F1', 4),
  ('Crypurrency Mix', 65000.40, 18.7, '0x2F1A7F0D8C4B6A1B6A1F1', 5),
  ('Energy Holdings', 80000.60, 14.3, '0x3D1C4D2C3B3E2D8C4B6A1F1', 6),
  ('Hehcare Investments', 100000.95, 20.1, null, 7),
  ('Development Fund', 110000.20, 10.9, '0xC4D2C1A7F0D8C4B6A1F1', 8),
  ('Emerging Portfolio', 95000.70, null, '0xB6A1F10x6E2F1A7F0D81', 9),
  ('Disified Holdings', 85000.55, 16.8, '0x7F0D8C4B6A1F10xF1', 10),
  ('Technology  Fund', 70000.45, 11.2, '0xE2F1A7F0D8C0D8C4B6A1F1', 11),
  ('Goods Investments', 88000.65, null, null, 12),
  ('Global Fund', 118000.75, 13.7, '0xB3E2F1A7F0D8F0D8C4B6A1F1', 13),
  ('Bioch Holdings', 72000.50, 21.8, '0x2F1A7F0D8C4B6C4B6A1F1', 14),
  ('Global Stocks', 105000.90, null, null, 15),
  ('Financial Fund', 99000.85, 15.2, '0x9F1A7F0D8C4B6A1F101F1', 16),
  ('Tech Opponities', 83000.60, 14.5, null, 17),
  ('Energy Holdings', 96000.75, 18.3, '0x6A09F56C7F3DD8C4B6A1F1', 18),
  ('Random Holdings', 92000.35, 14.1, '0x7F0D8C4B6A1F10xF1', 6),
  ('Azbest Fund', 68000.60, 10.5, '0xE2F1A7F0D8C0D8C4B6A1F1', 6),
  ('True Investments', 86000.7, 18.2, null, 6),
  ('Local Fund', 115000.90, 12.3, '0xB3E2F1A7F0D8F0D8C4B6A1F1', 2),
  ('FinT Holdings', 74000.45, 20.6, '0x2F1A7F0D8C4B6C4B6A1F1', 2),
  ('Roll Stocks', 107000.80, null, null, 15),
  ('Dropped Fund', 101000.65, 14.9, '0x9F1A7F0D8C4B6A1F101F1', 15),
  ('Tech Lost', 85000.70, 13.8, null, 17),
  ('AB Holdings', 92000.80, 16.5, '0x6A09F56C7F3DD8C4B6A1F1', 18);
----------------------------------------------------------------
INSERT INTO Transactions (Volume, Value, Date, Portfolio_ID, Cryptocurrency_ID)
VALUES
    (0.385, null, '2023-01-15T08:30:00', 1, 1),
    (3.65, null, '2023-02-21T14:45:00', 4, 3),
    (1.25, null, '2023-03-10T10:15:00', 2, 2),
    (2.75, null, null, 3, 4),
    (0.95, null, '2023-04-05T18:20:00', 5, 1),
    (4.2, null, '2023-05-12T11:30:00', 1, 3),
    (0.75, null, null, 2, 4),
    (2.1, null, '2023-06-08T09:00:00', 3, 2),
    (1.8, null, '2023-07-17T16:40:00', 4, 1),
    (3.3, null, '2023-08-23T12:55:00', 5, 3),
    (0.5, null, null, 1, 2),
    (1.65, null, '2023-09-30T14:10:00', 4, 4),
    (2.95, null, '2023-10-14T20:05:00', 2, 1),
    (0.85, null, '2023-11-19T13:25:00', 3, 3),
    (4.5, null, '2023-12-03T17:45:00', 5, 2),
    (1.15, null, null, 1, 4),
    (3.8, null, '2024-01-07T19:50:00', 2, 3),
    (0.65, null, '2024-02-11T22:15:00', 3, 1),
    (2.45, null, null, 4, 2),
    (1.45, null, null, 8, 2),
    (4.05, null, '2024-06-30T10:10:00', 9, 4),
    (0.95, null, '2024-07-15T18:45:00', 10, 1),
    (2.8, null, null, 11, 3),
    (1.1, null, '2024-08-20T11:20:00', 12, 2),
    (3.6, null, '2024-09-25T09:00:00', 13, 1),
    (0.75, null, '2024-10-30T15:15:00', 14, 4),
    (2.3, null, null, 15, 2),
    (1.8, null, '2024-11-05T20:45:00', 16, 3),
    (3.25, null, '2024-12-10T13:30:00', 17, 1),
    (0.55, null, null, 18, 4),
    (1.9, null, '2025-01-14T19:55:00', 1, 3),
    (2.65, null, '2025-02-18T22:10:00', 2, 1),
    (0.45, null, null, 3, 2),
    (3.4, null, '2025-03-25T15:40:00', 4, 4),
    (1.25, null, '2025-04-29T18:00:00', 5, 1),
    (2.95, null, null, 6, 3),
    (0.8, null, '2025-05-04T12:25:00', 7, 2),
    (4.15, null, '2025-06-08T10:45:00', 8, 1),
    (1.6, null, null, 9, 3),
    (3.05, null, '2025-07-13T16:20:00', 10, 2);
----------------------------------------------------------------
INSERT INTO Vexels (Location, User_ID)
VALUES
    ('Dhali', 20),
    ('New York', 1),
    ('Tokyo', 4),
    ('London', 5),
    ('Paris', 6),
    ('Sydney', 12),
    ('Berlin', 10),
    ('Los Angeles', 13),
    ('Shanghai', 17),
    ('Dubai', 19),
    ('Singapore', 7),
    ('Prague', 14)
----------------------------------------------------------------
INSERT INTO P2P_Offers (Volume, Value, Place, Status, Negotiable, Cryptocurrency_ID, Trader_ID)
VALUES
    (0.5, 20561.0, 'New York', 3, 0, 1, 1),
    (1.8, 4321.0, 'Tokyo', 3, 0, 2, 1),
    (3.2, 751.0, 'London', 3, 0, 3, 3),
    (1.0, 782.0, 'Paris', 3, 0, 1, 4),
    (4.5, 242.0, 'Sydney', 2, 0, 5, 5),
    (2.0, 78224.0, 'Berlin', 2, 1, 1, 6),
    (3.8, 78.0, 'Los Angeles', 2, 1, 1, 1),
    (1.2, 34.0, 'Shanghai', 1, 0, 3, 8),
    (2.7, 7375.0, 'Dubai', 1, 1, 4, 9),
    (3.5, 5200.0, 'Singapore', 1, 1, 5, 1);
----------------------------------------------------------------
INSERT INTO P2P_Transaction (Date, Offer_ID)
VALUES
    ('2019-01-15T08:30:00', 1),
    ('2021-02-21T14:45:00', 2),
    ('2022-03-10T10:15:00', 3),
    ('2023-11-19T13:25:00', 4);
----------------------------------------------------------------