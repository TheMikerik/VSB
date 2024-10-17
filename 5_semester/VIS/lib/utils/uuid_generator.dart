import 'dart:math';

class UUIDGenerator {
  static String generateUUID() {
    final Random random = Random();
    const String hexDigits = '0123456789abcdef';
    String uuid = '';
    for (int i = 0; i < 32; i++) {
      uuid += hexDigits[random.nextInt(16)];
      if ([8, 12, 16, 20].contains(i + 1)) {
        uuid += '-';
      }
    }
    return uuid;
  }
}
