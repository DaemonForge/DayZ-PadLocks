# PadLocks Mod — Comprehensive Player Guide

> **Purpose of this document:** This is a complete player-facing reference for the PadLocks mod for DayZ. It covers every item, every interaction, the UI, raiding mechanics, repair mechanics, and server configuration behavior that affects players. Feed this document along with the server's `config.json` to an AI to generate tailored knowledge-base articles for your community.

---

## Table of Contents

1. [Overview](#1-overview)
2. [Items](#2-items)
   - 2.1 [Padlock (Standard)](#21-padlock-standard)
   - 2.2 [Heavy Duty Padlock](#22-heavy-duty-padlock)
   - 2.3 [Bolt Cutter](#23-bolt-cutter)
   - 2.4 [Lock Smith Repair Kit](#24-lock-smith-repair-kit)
3. [How Padlocks Work](#3-how-padlocks-work)
   - 3.1 [Attaching a Padlock](#31-attaching-a-padlock)
   - 3.2 [Setting a PIN](#32-setting-a-pin)
   - 3.3 [Opening / Unlocking a Padlocked Door](#33-opening--unlocking-a-padlocked-door)
   - 3.4 [The "Remembered Players" System](#34-the-remembered-players-system)
   - 3.5 [Resetting (Clearing) the PIN](#35-resetting-clearing-the-pin)
   - 3.6 [PIN Code Length (4-Digit vs 6-Digit)](#36-pin-code-length-4-digit-vs-6-digit)
4. [The Padlock UI](#4-the-padlock-ui)
   - 4.1 [Opening the UI](#41-opening-the-ui)
   - 4.2 [UI Controls](#42-ui-controls)
   - 4.3 [Notifications](#43-notifications)
5. [Raiding — Cutting Padlocks](#5-raiding--cutting-padlocks)
   - 5.1 [Requirements](#51-requirements)
   - 5.2 [How Cutting Works](#52-how-cutting-works)
   - 5.3 [What Happens When a Padlock Is Destroyed](#53-what-happens-when-a-padlock-is-destroyed)
   - 5.4 [Raid-Blocked Items](#54-raid-blocked-items)
6. [Repairing Padlocks](#6-repairing-padlocks)
7. [Rate Limiting & Anti-Brute-Force](#7-rate-limiting--anti-brute-force)
8. [Compatibility Notes](#8-compatibility-notes)
9. [Quick Reference Table](#9-quick-reference-table)

---

## 1. Overview

The **PadLocks** mod adds a physical padlock security system to DayZ base building. Instead of (or in addition to) the vanilla combination lock, players can attach padlocks to fence gates and other compatible structures. Padlocks use a numeric PIN code that players set and enter via an in-game UI dial interface.

**Key features:**
- Two padlock tiers: Standard and Heavy Duty
- 4-digit or 6-digit PIN codes (server-configurable)
- Bolt cutters for raiding padlocked doors
- Repair kit for restoring damaged padlocks
- "Remembered players" system — once you enter the correct PIN, you can open the door freely without re-entering it (until the PIN is reset)
- Rate limiting to prevent brute-force PIN guessing
- Full admin logging of all padlock interactions
- 12-language localization support

---

## 2. Items

### 2.1 Padlock (Standard)

| Property | Value |
|---|---|
| **In-Game Name** | Padlock |
| **Description** | A simple padlock for securing your belongings. |
| **Inventory Size** | 1×2 (1 wide, 2 tall) |
| **Weight** | 650g |
| **Health (HP)** | 863 |

The standard padlock is the basic security option. It can be attached to any fence gate slot that accepts a padlock (or the vanilla combination lock slot). It has moderate health, making it vulnerable to bolt cutters but still requiring significant effort to cut through.

### 2.2 Heavy Duty Padlock

| Property | Value |
|---|---|
| **In-Game Name** | Heavy Duty Padlock |
| **Description** | A heavy duty padlock for maximum security. |
| **Inventory Size** | 2×3 (2 wide, 3 tall) |
| **Weight** | 1,200g |
| **Health (HP)** | 2,875 |

The heavy duty padlock is the premium security option. It has **over 3× the health** of the standard padlock, making it significantly harder to raid. It takes up more inventory space and weighs more, but provides much greater protection. Uses the same PIN system and UI as the standard padlock.

### 2.3 Bolt Cutter

| Property | Value |
|---|---|
| **In-Game Name** | Bolt Cutter |
| **Description** | A bolt cutter that can be used to cut padlocks. |
| **Inventory Size** | 2×5 (2 wide, 5 tall) |
| **Weight** | 2,600g |
| **Health (HP)** | 450 |
| **Carry Slots** | Shoulder, Melee |
| **Loot Category** | Tools |

The bolt cutter is the only tool that can be used to raid (cut through) a padlock. It is a two-handed item that can be carried on the shoulder or in a melee slot. The bolt cutter takes damage each time it is used to cut a padlock, so it has limited uses before it breaks.

### 2.4 Lock Smith Repair Kit

| Property | Value |
|---|---|
| **In-Game Name** | Lock Smith Repair Kit |
| **Description** | A kit that can repair padlocks. |
| **Inventory Size** | 2×3 (2 wide, 3 tall) |
| **Weight** | 1,200g |
| **Health (HP)** | 50 |
| **Uses** | Percentage-based (starts at 100%, consumed per repair) |

The repair kit restores health to damaged padlocks. It uses DayZ's standard repair system — combine the repair kit with a padlock in your inventory or vicinity to repair it. The kit is consumed based on how much repair is done (percentage-based quantity).

---

## 3. How Padlocks Work

### 3.1 Attaching a Padlock

1. **Have a padlock** (Standard or Heavy Duty) in your inventory.
2. **Approach a fence gate** (or other compatible base-building element).
3. **Attach the padlock** to the structure using the inventory attachment system. Padlocks fit into the vanilla combination lock slot (`Att_CombinationLock`) as well as dedicated padlock slots (`Att_Padlock1` through `Att_Padlock12`).
4. Once attached, the padlock is visible on the structure but is **not yet locked** — it has no PIN set.

> **Important:** A padlock that is attached but has no PIN set is not locked. Anyone can interact with it to set the first PIN.

### 3.2 Setting a PIN

1. **Approach the fence** with an attached padlock that does not yet have a PIN.
2. You will see the action **"Set Padlock Pin"** appear.
3. **Interact** to open the PIN dial interface.
4. **Enter your desired PIN** using the dial (4 or 6 digits depending on server configuration).
5. **Press the Lock/Set button** on the UI.
6. The padlock is now **locked** with your chosen PIN. The door/gate will close and lock.

> **The player who sets the PIN is automatically "remembered"** and will not need to enter the PIN again to open the door (see Section 3.4).

### 3.3 Opening / Unlocking a Padlocked Door

There are two ways a padlocked door can be opened:

#### If You Are a Remembered Player
- Simply use the **"Unlock Padlocked Door"** action on the fence.
- The door opens immediately — no PIN entry required.

#### If You Are NOT a Remembered Player
- Use the **"Unlock Padlocked Door"** action.
- The **PIN dial UI** will open.
- Enter the correct PIN and press the **Unlock button**.
- If the PIN is correct:
  - The door opens.
  - **You are now added to the remembered players list** — future opens won't require the PIN.
- If the PIN is incorrect:
  - You receive an **"Invalid Pin"** notification.
  - You must wait before trying again (rate limiting applies — see Section 7).

#### Alternative: Manage Lock Action
- If you see **"Manage Lock"** as an action, this is a continuous (hold) action that opens the lock UI.
- This is available on locked padlocks and allows you to enter the PIN or reset it.

### 3.4 The "Remembered Players" System

Once a player successfully enters the correct PIN for a padlock, their player ID is stored in the padlock's **remembered players list**. This means:

- **They can open that door instantly** without entering the PIN again.
- This persists across server restarts (the list is saved with the padlock).
- **Multiple players can be remembered** — every player who enters the correct PIN gets added.
- The remembered list is **cleared when the PIN is reset** (see Section 3.5).

> **Tip:** Share the PIN with your group members. Once each person enters it once, they'll all have easy access going forward.

### 3.5 Resetting (Clearing) the PIN

To reset a padlock's PIN (removing the lock entirely):

1. Open the padlock UI on a **locked** padlock (the Reset button is only visible when a PIN is set).
2. **Enter the current PIN** using the dials.
3. **Press the Reset button**.
4. If the PIN is correct:
  - The padlock becomes **unlocked** (no PIN set).
  - The **remembered players list is cleared**.
  - The padlock can be removed from the structure or a new PIN can be set.
- If the PIN is incorrect:
  - You receive an **"Invalid Pin"** notification.
  - Rate limiting applies.

> **Warning:** Resetting the PIN clears ALL remembered players. Everyone will need to re-enter the new PIN.

### 3.6 PIN Code Length (4-Digit vs 6-Digit)

The server administrator configures whether padlocks use **4-digit** or **6-digit** PIN codes:

- **4-digit mode** (default): PINs range from `0000` to `9999` (10,000 possible combinations).
- **6-digit mode**: PINs range from `000000` to `999999` (1,000,000 possible combinations).

This is a server-wide setting — all padlocks on the server use the same digit count. The UI automatically adjusts to show either 4 or 6 dials.

> **Players cannot choose which mode to use** — it is determined by the server's configuration.

---

## 4. The Padlock UI

### 4.1 Opening the UI

The padlock dial interface opens automatically when:
- You attempt to **set a PIN** on a newly attached padlock.
- You attempt to **unlock** a padlocked door and you are not a remembered player.
- You use the **"Manage Lock"** continuous action on a locked padlock.

### 4.2 UI Controls

The UI displays a visual padlock image with rotating number dials:

| Control | Function |
|---|---|
| **Up arrows (▲)** | Increment the digit below by 1 (wraps from 9 → 0) |
| **Down arrows (▼)** | Decrement the digit above by 1 (wraps from 0 → 9) |
| **Digit boxes** | Click to clear, then type a digit directly. Auto-advances to next digit. |
| **Lock/Unlock button** | Submits the current PIN. Sets the PIN (if none set) or attempts to unlock. |
| **Reset button** | Attempts to clear the PIN using the entered combination. Only visible when a PIN is already set. |
| **ESC / Back** | Closes the UI without submitting. |

**Typing directly into digit boxes:**
- Click a digit box to select it.
- Type a number (0–9). Only numeric input is accepted.
- The cursor automatically advances to the next digit box after entry.
- If you type a number, it will replace the current number in the box.

**Visual feedback:**
- When no PIN is set, the UI shows a **"Set"** visual (lock icon in set/locked state).
- When a PIN is already set, the UI shows an **"Unlock"** visual.
- Hovering over the Unlock/Set button will show a tooltip indicating the action.
- Hovering over the Reset button will show a tooltip indicating the action.

### 4.3 Notifications

| Notification | Meaning |
|---|---|
| **"Invalid Pin"** | The PIN you entered does not match the padlock's stored PIN. |
| **"Attempts Too Quick"** | You are being rate-limited for making too many PIN attempts too quickly. Wait before trying again. |

---

## 5. Raiding — Cutting Padlocks

### 5.1 Requirements

To cut (raid) a padlock, you need:
- A **Bolt Cutter** in hand (must not be ruined).
- A **padlocked structure** to target.
- The padlock must **not be ruined** already.
- The structure type must **not be on the server's Raid Block List** (see Section 5.4).

### 5.2 How Cutting Works

1. **Equip the Bolt Cutter**.
2. **Approach the padlocked structure**.
3. The **"Cut Padlock"** action appears.
4. **Hold the action button** — this is a continuous action with a progress bar.
5. While cutting:
   - The **padlock takes 4.5 damage per second**.
   - The **bolt cutter takes 2.5 damage per second**.
   - A progress bar shows how far through the padlock's health you are.
   - Every 75 damage dealt to the padlock, a log is generated and HAB action is triggered (if applicable).
6. You can **interrupt** the action at any time — all damage dealt so far is permanent.
7. When the padlock's health reaches zero, it is **destroyed and drops to the ground**, unlocking the structure.

**Time to cut through each padlock type (Default Config):**

| Padlock Type | Health | Time to Cut (approx.) |
|---|---|---|
| Standard Padlock | 863 HP | ~616 seconds (~10 min 16 sec) |
| Heavy Duty Padlock | 2,875 HP | ~2,054 seconds (~34 min 14 sec) |

> **Note:** These times assume continuous uninterrupted cutting. The bolt cutter itself has 450 HP and takes **0.8 damage/second**. **A single pristine bolt cutter can cut through approximately 91% of a Standard Padlock before breaking.** To cut a full health Standard Padlock, you will need 2 bolt cutters (or a repair kit).

**Bolt cutter durability per cut:**

| Padlock Health | Bolt Cutter HP Used | Bolt Cutters Needed |
|---|---|---|
| **Pristine (100%) Standard** | ~493 HP | 2 (1 breaks near end) |
| **Damaged (90%) Standard** | ~444 HP | **1** (barely survives) |
| **Heavy Duty (100%)** | ~1,643 HP | 4 |

### 5.3 What Happens When a Padlock Is Destroyed

When a padlock is cut through (HP reaches 0):
1. The padlock **drops to the ground** near the structure.
2. The padlock's **PIN is cleared**.
3. The padlock's **remembered players list is cleared**.
4. The structure becomes **unlocked** — anyone can open it freely.
5. The padlock entity itself is **ruined** (0 HP) but still exists as a dropped item.

### 5.4 Raid-Blocked Items

Server administrators can configure a **Raid Block List** — a list of structure class names that cannot be raided with bolt cutters. If a structure is on this list, the "Cut Padlock" action will not appear even if you have bolt cutters.

> **Check with your server admin** to find out if any structures are raid-blocked.

---

## 6. Repairing Padlocks

Padlocks can be repaired using the **Lock Smith Repair Kit**:

1. Have the **Lock Smith Repair Kit** and the **padlock** accessible (in inventory or nearby).
2. **Combine** the repair kit with the padlock (drag one onto the other in inventory).
3. The standard DayZ repair crafting recipe will execute.
4. The padlock's health is restored, and the repair kit's quantity decreases.

**Repair rules:**
- The repair kit must not be ruined.
- The padlock must be damaged (not pristine) and not fully ruined (damage level 0–3).
- The repair kit uses DayZ's built-in `PluginRepairing` system — the amount repaired depends on the kit's remaining quantity and the padlock's repair cost.

**Repair costs (from config):**
| Padlock Type | Repair Cost |
|---|---|
| Standard Padlock | 50.0 |
| Heavy Duty Padlock | 100.0 |

> **Tip:** Repair your padlocks periodically, especially if you suspect someone has been attempting to cut them. A partially-damaged padlock is much easier to finish off.

---

## 7. Rate Limiting & Anti-Brute-Force

The mod includes a progressive rate-limiting system to prevent brute-force PIN guessing:

- After each PIN attempt (whether unlock or reset), there is a **minimum 4-second cooldown** before the next attempt.
- If you attempt to enter a PIN before the cooldown expires, you receive the **"Attempts Too Quick"** notification and the cooldown is extended by ~2 seconds.
- **Failed attempts are tracked per player per padlock.** The more times a specific player fails on the same padlock, the longer the delay between allowed attempts becomes.
- The delay formula is progressive: after each failed attempt, the delay increases based on `3 seconds × attempt_count × max(1, attempt_count - 2)`.
- After **3+ failed attempts**, the event is logged to the server admin log.

**Approximate delays by consecutive failed attempt count:**

| Failed Attempt # | Minimum Wait Before Next Attempt |
|---|---|
| 1st Fail | 4 seconds |
| 2nd Fail | 6 seconds |
| 3rd Fail | 9 seconds |
| 4th Fail | 12 seconds |
| 5th Fail | 27 seconds |
| 6th Fail | 48 seconds |
| 7th+ Fail | Continues increasing exponentially |

> **Note:** There is also a global 4-second cooldown between *any* interaction (even successful ones). Spamming the button while on cooldown will extend your wait time by an additional 2 seconds per click. This system resets when the server restarts.

---

## 8. Compatibility Notes

- **Vanilla Combination Lock Slot:** Padlocks can attach to the standard `Att_CombinationLock` slot, meaning they work as a direct replacement for the vanilla combination lock on fences.
- **Multiple Padlock Slots:** Structures can support up to 12 padlock attachment slots (`Att_Padlock1` through `Att_Padlock12`), allowing for server mods that use multiple lock points.
- **Fence Compatibility:** The mod specifically overrides the `Fence` class to add padlock actions. Any structure inheriting from `Fence` (standard DayZ fences and fence gates) is compatible.
- **The mod replaces the "Open Door" action** on padlocked fences — instead of the vanilla open action, players see "Unlock Padlocked Door".
- **Localization:** The mod supports 12 languages: English, German, French, Spanish, Russian, Polish, Czech, Italian, Portuguese, Simplified Chinese, Japanese, and Korean.

---

## 9. Quick Reference Table

| Action | How | When Available |
|---|---|---|
| **Attach padlock** | Place padlock into structure's lock slot via inventory | Padlock in inventory, structure nearby |
| **Set PIN** | Interact with attached padlock → UI → enter PIN → press Set | Padlock attached, no PIN set, door closed |
| **Open door (remembered)** | "Unlock Padlocked Door" action | Padlocked door, you previously entered the correct PIN |
| **Open door (new)** | "Unlock Padlocked Door" → UI → enter PIN → Unlock | Padlocked door, you have NOT entered the PIN before |
| **Manage Lock** | Hold "Manage Lock" action (continuous) | Padlocked & locked door, door closed |
| **Reset PIN** | Open UI → enter current PIN → press Reset | Padlock has a PIN set |
| **Cut padlock** | Equip Bolt Cutter → "Cut Padlock" action (hold) | Bolt cutter in hand, padlocked structure, not raid-blocked |
| **Repair padlock** | Combine Lock Smith Repair Kit with padlock | Both items accessible, padlock is damaged |
| **Close UI** | Press ESC / Back | Padlock UI is open |
