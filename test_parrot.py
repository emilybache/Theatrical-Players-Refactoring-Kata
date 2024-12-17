import pytest
from unittest.mock import Mock, MagicMock
from parrot import Parrot, ParrotType


def test_european_parrot_speed():
    parrot = Parrot(ParrotType.EUROPEAN, 0, 0, False)
    assert parrot.speed() == 12.0


def test_african_parrot_speed_with_zero_coconuts():
    parrot = Parrot(ParrotType.AFRICAN, 0, 0, False)
    assert parrot.speed() == 12.0


def test_african_parrot_speed_with_two_coconuts():
    parrot = Parrot(ParrotType.AFRICAN, 2, 0, False)
    assert parrot.speed() == 0


def test_norwegian_blue_parrot_speed_with_nailed():
    parrot = Parrot(ParrotType.NORWEGIAN_BLUE, 0, 1.5, True)
    assert parrot.speed() == 0


def test_norwegian_blue_parrot_speed_with_voltage():
    parrot = Parrot(ParrotType.NORWEGIAN_BLUE, 0, 10, False)
    assert parrot.speed() == 24.0


# Тесты для метода cry
def test_european_parrot_cry():
    parrot = Parrot(ParrotType.EUROPEAN, 0, 0, False)
    assert parrot.cry() == "Sqoork!"


def test_norwegian_blue_parrot_cry_with_voltage():
    parrot = Parrot(ParrotType.NORWEGIAN_BLUE, 0, 10, False)
    assert parrot.cry() == "Bzzzzzz"


# Параметризованный тест
@pytest.mark.parametrize("type_of_parrot, number_of_coconuts, voltage, nailed, expected_speed", [
    (ParrotType.EUROPEAN, 0, 0, False, 12.0),
    (ParrotType.AFRICAN, 1, 0, False, 12.0 - 9.0 * 1),
    (ParrotType.NORWEGIAN_BLUE, 0, 15, False, 24.0),
    (ParrotType.NORWEGIAN_BLUE, 0, 5, True, 0),
])
def test_parrot_speed_parametrized(type_of_parrot, number_of_coconuts, voltage, nailed, expected_speed):
    parrot = Parrot(type_of_parrot, number_of_coconuts, voltage, nailed)
    assert parrot.speed() == expected_speed


# Тест с использованием моков
def test_speed_with_mocks(mocker):
    mock_base_speed = MagicMock(return_value=10.0)

    parrot = Parrot(ParrotType.EUROPEAN, 0, 0, False)
    # Заменяем метод _base_speed на MagicMock
    setattr(parrot, '_base_speed', mock_base_speed)

    # Проверяем, что скорость равна 10.0 (значение из мока)
    assert parrot.speed() == 10.0


# Тест с использованием мока для метода _load_factor
def test_load_factor_mock(mocker):
    mock_load_factor = MagicMock(return_value=10.0)
    parrot = Parrot(ParrotType.AFRICAN, 2, 0, False)
    setattr(parrot, '_load_factor', mock_load_factor)
    assert parrot.speed() == 0  # 12.0 - 10.0 * 2 < 0
