# PadLocks Mod — Server Config Reading Guide

> **Purpose of this document:** This guide explains how to read and interpret the PadLocks mod's `config.json` server configuration file. Feed this guide along with a specific server's `config.json` to an AI so it can produce accurate, server-specific player-facing KB articles that reflect that server's actual settings.

---

## Table of Contents

1. [Config File Location](#1-config-file-location)
2. [Config File Format](#2-config-file-format)
3. [Default Config](#3-default-config)
4. [Field-by-Field Reference](#4-field-by-field-reference)
   - 4.1 [ConfigVersion](#41-configversion)
   - 4.2 [Enable6NumberCodes](#42-enable6numbercodes)
   - 4.3 [RaidBlockList](#43-raidblocklist)
5. [How Config Values Affect Gameplay](#5-how-config-values-affect-gameplay)
6. [Example Configs & What They Mean for Players](#6-example-configs--what-they-mean-for-players)
7. [Instructions for AI Processing](#7-instructions-for-ai-processing)

---

## 1. Config File Location

The config file is located at:
```
<DayZ Server Profile Directory>/Padlock/config.json
```

Typically this resolves to something like:
```
C:\DayZServer\profiles\Padlock\config.json
```

- On first server start with the mod installed, the file is **auto-generated** with default values.
- The server reads this file on startup and sends the relevant settings to all connected clients.
- Changes require a **server restart** to take effect.

---

## 2. Config File Format

The file is standard **JSON**. All field names are case-sensitive and must match exactly.

```json
{
    "ConfigVersion": "0",
    "Enable6NumberCodes": 0,
    "RaidDamagePerSecond": 1.4,
    "RaidBlockList": [
        "SOMETHING"
    ]
}
```

---

## 3. Default Config

When the config file is first created, it contains these defaults:

```json
{
    "ConfigVersion": "0",
    "Enable6NumberCodes": 0,
    "RaidDamagePerSecond": 1.4,
    "RaidBlockList": [
        "SOMETHING"
    ]
}
```

The default `"SOMETHING"` in the RaidBlockList is a placeholder — it doesn't match any real in-game class name and has no effect. An empty list `[]` would behave identically.

---

## 4. Field-by-Field Reference

### 4.1 ConfigVersion

| Property | Details |
|---|---|
| **JSON Key** | `ConfigVersion` |
| **Type** | String |
| **Default** | `"0"` |
| **Player Impact** | None (internal tracking only) |

**What it is:** An internal version tracker for the config format. This is used by the mod developer to handle config migrations between mod updates. Server admins should generally leave this unchanged.

**How to read it:** Ignore this field when generating player-facing content. It has no gameplay effect.

---

### 4.2 Enable6NumberCodes

| Property | Details |
|---|---|
| **JSON Key** | `Enable6NumberCodes` |
| **Type** | Integer (`0` or `1`) |
| **Default** | `0` (disabled) |
| **Player Impact** | **HIGH** — changes the entire PIN system |

**What it is:** Controls whether padlocks use 4-digit or 6-digit PIN codes.

**How to read it:**

| Value | Meaning | PIN Range | Possible Combinations | UI Layout |
|---|---|---|---|---|
| `0` | **4-digit codes** (default) | `0000` – `9999` | 10,000 | 4 dial wheels |
| `1` | **6-digit codes** | `000000` – `999999` | 1,000,000 | 6 dial wheels |

**Player-facing implications:**
- **If `0` (4-digit):** Players set and enter 4-digit PINs. The padlock UI shows 4 number dials. Shorter PINs are easier to remember but have fewer combinations.
- **If `1` (6-digit):** Players set and enter 6-digit PINs. The padlock UI shows 6 number dials. More secure against brute-force guessing (100× more combinations), but longer to enter.
- This is a **server-wide setting** — all padlocks on the server use the same digit count. Players cannot choose individually.
- **Existing padlocks are NOT automatically converted** when this setting changes. Changing this mid-wipe may cause issues with existing locked padlocks.

---

### 4.3 RaidBlockList

| Property | Details |
|---|---|
| **JSON Key** | `RaidBlockList` |
| **Type** | Array of Strings |
| **Default** | `["SOMETHING"]` (placeholder, no real effect) |
| **Player Impact** | **HIGH** — determines which structures can be raided |

**What it is:** A list of **DayZ class names** (structure types) whose padlocks **cannot** be cut with bolt cutters. If a structure's class name appears in this list, the "Cut Padlock" action will not be available on it.

### 4.4 RaidDamagePerSecond

| Property | Details |
|---|---|
| **JSON Key** | `RaidDamagePerSecond` |
| **Type** | Float |
| **Default** | `1.4` |
| **Player Impact** | **HIGH** — determines raid duration |

**What it is:** The amount of damage a padlock takes per second while being cut with bolt cutters.

**How to read it:**

- **Higher values** = Faster raiding. Bolt cutter uses *less* total durability (fewer seconds).
- **Lower values** = Slower raiding. Bolt cutter uses *more* total durability (more seconds).
- **1.4** is the default (approx 10.3 mins for standard lock, uses ~110% of a bolt cutter).

**Configuration Examples & Raid Times:**

| `RaidDamagePerSecond` Value | Raid Speed | Time to Cut Standard (863 HP) | Bolt Cutters Needed (Standard) |
|---|---|---|---|
| **1.4** (Default) | Long Raid | **~10.3 mins** | **2** (Takes ~493 HP = ~110% cutter) |
| **1.6** | Balanced | ~9 mins | **1** (Takes ~431 HP = ~96% cutter) |
| **3.0** | Fast | ~4.8 mins | **1** (Takes ~230 HP) |
| **4.5** (Old Default) | Very Fast | ~3.2 mins | **1** (Takes ~153 HP) |
| **0.8** | Slow | ~18 mins | **2** (Takes ~863 HP = ~192% cutter) |

> **Note:**
> *   At **1.4 damage/sec** (default), a pristine bolt cutter **WILL BREAK** before finishing a standard padlock. You need a second tool or repair kit.
> *   At **1.6 damage/sec**, a pristine bolt cutter survives with ~4% health remaining.

---

---

**How to read it:**

The array contains string values. Each string is compared (case-insensitive) against the class name of the structure that the padlock is attached to.

**Examples of common DayZ structure class names that might appear:**

| Class Name | What It Is In-Game |
|---|---|
| `Fence` | Standard base-building fence/gate |
| `Watchtower` | Base-building watchtower |
| `"SOMETHING"` | Placeholder — matches nothing real |

**How the matching works (technical detail for accurate interpretation):**
1. When a player tries to cut a padlock, the mod checks the **parent structure's class name** (e.g., `Fence`).
2. It converts both the structure's class name and each entry in the RaidBlockList to **lowercase**.
3. If there is an **exact match**, the cut action is **blocked**.
4. The check is **exact string match only** — no wildcards, no partial matches.

**Player-facing implications:**

| RaidBlockList Value | What It Means for Players |
|---|---|
| `[]` (empty array) | All padlocked structures can be raided with bolt cutters |
| `["SOMETHING"]` (default) | All padlocked structures can be raided (placeholder matches nothing) |
| `["Fence"]` | Padlocks on fences CANNOT be cut — they are indestructible via bolt cutters |
| `["Fence", "Watchtower"]` | Padlocks on both fences and watchtowers cannot be cut |

> **Important:** This list blocks **bolt cutter raiding only**. Padlocks on blocked structures can still be unlocked by entering the correct PIN, and they can still be damaged by other means if the server has other mods that affect damage.

---

## 5. How Config Values Affect Gameplay

Here is a summary matrix showing how each config value maps to player experience:

| Config Value | Gameplay Area Affected | What Changes for Players |
|---|---|---|
| `Enable6NumberCodes = 0` | PIN entry UI, security level | 4 dials, 4-digit PINs, 10K combinations |
| `Enable6NumberCodes = 1` | PIN entry UI, security level | 6 dials, 6-digit PINs, 1M combinations |
| `RaidBlockList = []` | Raiding | All structures can be raided with bolt cutters |
| `RaidBlockList = ["Fence"]` | Raiding | Fences cannot be raided; other structures can |
| `RaidBlockList = ["Fence","X","Y"]` | Raiding | Listed structures cannot be raided; unlisted ones can |

---

## 6. Example Configs & What They Mean for Players

### Example A: Default / Vanilla-Like Config
```json
{
    "ConfigVersion": "0",
    "Enable6NumberCodes": 0,
    "RaidBlockList": ["SOMETHING"]
}
```
**For players:** Standard 4-digit PINs. All padlocked structures can be raided with bolt cutters. This is the most "vanilla" experience.

---

### Example B: High-Security, No-Raid Server
```json
{
    "ConfigVersion": "0",
    "Enable6NumberCodes": 1,
    "RaidBlockList": ["Fence", "Watchtower"]
}
```
**For players:** 6-digit PINs (much harder to guess). Padlocks on fences and watchtowers are completely immune to bolt cutters. Bolt cutters are only useful for other modded structures not in the block list. Bases are very secure — the only way in is knowing the PIN.

---

### Example C: Easy-Raid Server with Long PINs
```json
{
    "ConfigVersion": "0",
    "Enable6NumberCodes": 1,
    "RaidBlockList": []
}
```
**For players:** 6-digit PINs for maximum code security, but all structures can still be raided with bolt cutters. Good for servers that want secure codes but still allow physical raiding.

---

### Example D: 4-Digit with Selective Protection
```json
{
    "ConfigVersion": "0",
    "Enable6NumberCodes": 0,
    "RaidDamagePerSecond": 1.5,
    "RaidBlockList": ["Watchtower"]
}
```
**For players:** Standard 4-digit PINs. Fences can be raided with bolt cutters, but watchtower padlocks are immune. This creates a tier system where watchtowers are premium secure locations.

---

## 7. Instructions for AI Processing

When you receive a server's `config.json` along with this guide, follow these steps to generate accurate player-facing content:

### Step 1: Identify the PIN mode
- Read `Enable6NumberCodes`.
- If `0` → tell players they use **4-digit PINs** with **4 dial wheels** in the UI.
- If `1` → tell players they use **6-digit PINs** with **6 dial wheels** in the UI.

### Step 2: Determine raid rules
- Read `RaidBlockList`.
- If empty or contains only non-real class names (like `"SOMETHING"`) → tell players **all structures can be raided** with bolt cutters.
- If it contains real class names → list which structures are **protected** and which are **raidable**.
- Common class names to watch for:
  - `Fence` = standard fence gates
  - `Watchtower` = watchtowers
  - Any other string = likely a modded structure; include it by name.

### Step 3: Calculate derived values
Use these formulas for raid time estimates:

```
Padlock damage per second from bolt cutters = RaidDamagePerSecond (default 1.4 HP/sec)
Bolt cutter self-damage per second = 0.8 HP/sec
Bolt cutter total HP = 450

Standard Padlock HP = 863
Heavy Duty Padlock HP = 2875

Time to cut Standard Padlock = 863 / RaidDamagePerSecond
Time to cut Heavy Duty Padlock = 2875 / RaidDamagePerSecond

Bolt cutters needed for Standard = ceil((863 / RaidDamagePerSecond) / (450 / 0.8))
Bolt cutters needed for Heavy Duty = ceil((2875 / RaidDamagePerSecond) / (450 / 0.8))
```

> Note: `Bolt cutter self-damage per second` and `HP` values are hardcoded in the mod's scripts and are NOT configurable. They are constants. Only `RaidDamagePerSecond` is configurable.

### Step 4: Generate player-facing content
With the above information, produce:
1. **"How to Lock Your Base"** — step-by-step guide using the correct PIN length.
2. **"How to Unlock a Door"** — include remembered player system.
3. **"How to Raid"** — include which structures can/cannot be raided, time estimates, bolt cutter requirements.
4. **"Items Guide"** — all 4 items with stats.
5. **"FAQ"** — common questions based on the server's specific config.

### Step 5: Server-specific notes
Always include:
- The PIN length this server uses.
- Which structures (if any) are raid-protected.
- A reminder that the remembered player system means you only need to enter the PIN once.
- A warning about rate limiting for wrong PIN attempts.

---

## Appendix: All Hardcoded Values (Not in Config)

These values are baked into the mod's code and cannot be changed via `config.json`. Include them for completeness:

| Constant | Value | Description |
|---|---|---|
| Standard Padlock HP | 863 | Health points (15% buffed) |
| Heavy Duty Padlock HP | 2,875 | Health points (15% buffed) |
| Bolt Cutter HP | 450 | Health points |
| Repair Kit HP | 50 | Health points |
| Start Raid Damage | 1.4 HP/sec | Default damage to padlock (Configurable) |
| Bolt cutter damage | 0.8 HP/sec | Self-damage to bolt cutter while cutting |
| Standard Padlock weight | 650g | Inventory weight |
| Heavy Duty Padlock weight | 1,200g | Inventory weight |
| Bolt Cutter weight | 2,600g | Inventory weight |
| Repair Kit weight | 1,200g | Inventory weight |
| Standard Padlock size | 1×2 | Inventory slots |
| Heavy Duty Padlock size | 2×3 | Inventory slots |
| Bolt Cutter size | 2×5 | Inventory slots |
| Repair Kit size | 2×3 | Inventory slots |
| Rate limit base cooldown | ~3-4 seconds | Per attempt |
| Rate limit escalation | Progressive (exponential) | Increases with each failed attempt |
| Max action distance | 5 meters | PIN attempts rejected if player is further away |
| PIN attempt admin log threshold | 3 failed attempts | Triggers admin log warning |
| Standard Padlock repair cost | 50.0 | Repair kit usage per repair |
| Heavy Duty Padlock repair cost | 100.0 | Repair kit usage per repair |
